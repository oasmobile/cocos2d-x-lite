/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "AssetsManagerEx.h"
#include "CCEventListenerAssetsManagerEx.h"
#include "base/ccUTF8.h"
#include "base/CCDirector.h"

#include <stdio.h>

#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip/unzip.h"
#endif
#include "base/CCAsyncTaskPool.h"

NS_CC_EXT_BEGIN

#define VERSION_FILENAME        "version.manifest"
#define TEMP_MANIFEST_FILENAME  "project.manifest.temp"
#define TEMP_PACKAGE_SUFFIX     "_temp"
#define MANIFEST_FILENAME       "project.manifest"
#define MANIFEST_FILENAME_ZIP   "project.manifest.zip"
#define VERSION_FILENAME_ZIP    "version.manifest.zip"
#define ZIP_SUFFIX              ".zip"
#define TEMP_SUFFIX             ".temp"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

#define DEFAULT_CONNECTION_TIMEOUT 45

#define SAVE_POINT_INTERVAL 0.1

const std::string AssetsManagerEx::VERSION_ID = "@version";
const std::string AssetsManagerEx::MANIFEST_ID = "@manifest";

// Implementation of AssetsManagerEx

AssetsManagerEx::AssetsManagerEx(const std::string& manifestUrl, const std::string& storagePath)
: _updateState(State::UNINITED)
, _assets(nullptr)
, _storagePath("")
, _tempVersionPath("")
, _cacheManifestPath("")
, _tempManifestPath("")
, _localManifest(nullptr)
, _tempManifest(nullptr)
, _remoteManifest(nullptr)
, _updateEntry(UpdateEntry::NONE)
, _percent(0)
, _percentByFile(0)
, _totalSize(0)
, _sizeCollected(0)
, _totalDownloaded(0)
, _totalToDownload(0)
, _totalWaitToDownload(0)
, _nextSavePoint(0.0)
, _downloadResumed(false)
, _maxConcurrentTask(32)
, _currConcurrentTask(0)
, _verifyCallback(nullptr)
,_project_compress(false)
,_version_compress(false)
, _inited(false)
{
    init(manifestUrl, storagePath);
}

AssetsManagerEx::AssetsManagerEx(const std::string& manifestUrl, const std::string& storagePath, const VersionCompareHandle& handle)
: _updateState(State::UNINITED)
, _assets(nullptr)
, _storagePath("")
, _tempVersionPath("")
, _cacheManifestPath("")
, _tempManifestPath("")
, _localManifest(nullptr)
, _tempManifest(nullptr)
, _remoteManifest(nullptr)
, _updateEntry(UpdateEntry::NONE)
, _percent(0)
, _percentByFile(0)
, _totalSize(0)
, _sizeCollected(0)
, _totalDownloaded(0)
, _totalToDownload(0)
, _totalWaitToDownload(0)
, _nextSavePoint(0.0)
, _downloadResumed(false)
, _maxConcurrentTask(32)
, _currConcurrentTask(0)
, _versionCompareHandle(handle)
, _verifyCallback(nullptr)
,_project_compress(false)
,_version_compress(false)
, _inited(false)
{
    init(manifestUrl, storagePath);
}

void AssetsManagerEx::init(const std::string& manifestUrl, const std::string& storagePath)
{
    // Init variables
    _eventDispatcher = Director::getInstance()->getEventDispatcher();
    std::string pointer = StringUtils::format("%p", this);
    _eventName = EventListenerAssetsManagerEx::LISTENER_ID + pointer;
    _fileUtils = FileUtils::getInstance();

    network::DownloaderHints hints =
    {
        static_cast<uint32_t>(_maxConcurrentTask),
        DEFAULT_CONNECTION_TIMEOUT,
        ".tmp"
    };
    _downloader = std::shared_ptr<network::Downloader>(new network::Downloader(hints));
    _downloader->onTaskError = std::bind(&AssetsManagerEx::onError, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    _downloader->onTaskProgress = [this](const network::DownloadTask& task,
                                         int64_t /*bytesReceived*/,
                                         int64_t totalBytesReceived,
                                         int64_t totalBytesExpected)
    {
        this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
    };
    _downloader->onFileTaskSuccess = [this](const network::DownloadTask& task)
    {
        this->onSuccess(task.requestURL, task.storagePath, task.identifier);
    };
    setStoragePath(storagePath);
    _tempVersionPath = _tempStoragePath + VERSION_FILENAME;
    _cacheManifestPath = _storagePath + MANIFEST_FILENAME;
    _tempManifestPath = _tempStoragePath + TEMP_MANIFEST_FILENAME;

    if (manifestUrl.size() > 0)
    {
        loadLocalManifest(manifestUrl);
    }
}

AssetsManagerEx::~AssetsManagerEx()
{
    _downloader->onTaskError = (nullptr);
    _downloader->onFileTaskSuccess = (nullptr);
    _downloader->onTaskProgress = (nullptr);
    CC_SAFE_RELEASE(_localManifest);
    // _tempManifest could share a ptr with _remoteManifest or _localManifest
    if (_tempManifest != _localManifest && _tempManifest != _remoteManifest)
        CC_SAFE_RELEASE(_tempManifest);
    CC_SAFE_RELEASE(_remoteManifest);
}

AssetsManagerEx* AssetsManagerEx::create(const std::string& manifestUrl, const std::string& storagePath)
{
    AssetsManagerEx* ret = new (std::nothrow) AssetsManagerEx(manifestUrl, storagePath);
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void AssetsManagerEx::initManifests()
{
    _inited = true;
    // Init and load temporary manifest
     cocos2d::log("AssetsManagerEx : initManifests---------------00000\n");
    _tempManifest = new (std::nothrow) Manifest();
    if (_tempManifest)
    {
        cocos2d::log("AssetsManagerEx : initManifests---------------11111\n");
        _tempManifest->parseFile(_tempManifestPath);
        // Previous update is interrupted
        if (_fileUtils->isFileExist(_tempManifestPath))
        {
            cocos2d::log("AssetsManagerEx : initManifests---------------22222\n");
            // Manifest parse failed, remove all temp files
            if (!_tempManifest->isLoaded())
            {
                cocos2d::log("AssetsManagerEx : initManifests---------------33333\n");
                _fileUtils->removeDirectory(_tempStoragePath);
                CC_SAFE_RELEASE(_tempManifest);
                _tempManifest = nullptr;
            }
        }
    }
    else
    {
        cocos2d::log("AssetsManagerEx : initManifests---------------44444\n");
        _inited = false;
    }
    
    // Init remote manifest for future usage
    _remoteManifest = new (std::nothrow) Manifest();
    if (!_remoteManifest)
    {
        _inited = false;
    }
    
    if (!_inited)
    {
        CC_SAFE_RELEASE(_localManifest);
        CC_SAFE_RELEASE(_tempManifest);
        CC_SAFE_RELEASE(_remoteManifest);
        _localManifest = nullptr;
        _tempManifest = nullptr;
        _remoteManifest = nullptr;
    }
}

void AssetsManagerEx::prepareLocalManifest()
{
    cocos2d::log("AssetsManagerEx : prepareLocalManifest---------------------\n");
    // An alias to assets
    _assets = &(_localManifest->getAssets());

    // Add search paths
    _localManifest->prependSearchPaths();
}

bool AssetsManagerEx::loadLocalManifest(Manifest* localManifest, const std::string& storagePath)
{
    cocos2d::log("AssetsManagerEx : loadLocalManifest---------------\n");
    if (_updateState > State::UNINITED)
    {
        return false;
    }
    if (!localManifest || !localManifest->isLoaded())
    {
        return false;
    }
    _inited = true;
    // Reset storage path
    if (storagePath.size() > 0)
    {
        setStoragePath(storagePath);
        _tempVersionPath = _tempStoragePath + VERSION_FILENAME;
        _cacheManifestPath = _storagePath + MANIFEST_FILENAME;
        _tempManifestPath = _tempStoragePath + TEMP_MANIFEST_FILENAME;
    }
    // Release existing local manifest
    if (_localManifest)
    {
        CC_SAFE_RELEASE(_localManifest);
    }
    
    cocos2d::log("AssetsManagerEx : loadLocalManifest---------------00000\n");
    _localManifest = localManifest;
    _localManifest->retain();
    // Find the cached manifest file
    Manifest *cachedManifest = nullptr;
    cocos2d::log("AssetsManagerEx : loadLocalManifest---------------11111\n");
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
         cocos2d::log("AssetsManagerEx : loadLocalManifest---------------2222\n");
        cachedManifest = new (std::nothrow) Manifest();
        if (cachedManifest)
        {
            cachedManifest->parseFile(_cacheManifestPath);
            if (!cachedManifest->isLoaded())
            {
                _fileUtils->removeFile(_cacheManifestPath);
                CC_SAFE_RELEASE(cachedManifest);
                cachedManifest = nullptr;
            }
        }
    }
    // Compare with cached manifest to determine which one to use
    if (cachedManifest)
    {
         cocos2d::log("AssetsManagerEx : loadLocalManifest---------------33333\n");
        bool localNewer = _localManifest->versionGreater(cachedManifest, _versionCompareHandle);
        if (localNewer)
        {
             cocos2d::log("AssetsManagerEx : loadLocalManifest---------------44444\n");
            // Recreate storage, to empty the content
            _fileUtils->removeDirectory(_storagePath);
            _fileUtils->createDirectory(_storagePath);
            CC_SAFE_RELEASE(cachedManifest);
        }
        else
        {
             cocos2d::log("AssetsManagerEx : loadLocalManifest---------------5555\n");
            CC_SAFE_RELEASE(_localManifest);
            _localManifest = cachedManifest;
        }
    }
    prepareLocalManifest();
    
    // Init temp manifest and remote manifest
    initManifests();
    
    if (!_inited)
    {
        return false;
    }
    else
    {
        _updateState = State::UNCHECKED;
        return true;
    }
}

bool AssetsManagerEx::loadLocalManifest(const std::string& manifestUrl)
{
     cocos2d::log("AssetsManagerEx : loadLocalManifest---------------------manifestUrl----------a\n");
    if (manifestUrl.size() == 0)
    {
        return false;
    }
    if (_updateState > State::UNINITED)
    {
        return false;
    }
    _manifestUrl = manifestUrl;
    // Init and load local manifest
    _localManifest = new (std::nothrow) Manifest();
    if (!_localManifest)
    {
        return false;
    }
    
    cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------b\n");
    Manifest *cachedManifest = nullptr;
    // Find the cached manifest file
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
        cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------00000\n");
        cachedManifest = new (std::nothrow) Manifest();
        if (cachedManifest)
        {
            cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------11111\n");
            cachedManifest->parseFile(_cacheManifestPath);
            if (!cachedManifest->isLoaded())
            {
                cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------22222\n");
                _fileUtils->removeFile(_cacheManifestPath);
                CC_SAFE_RELEASE(cachedManifest);
                cachedManifest = nullptr;
            }
        }
    }
    
    cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------33333\n");
    // Ensure no search path of cached manifest is used to load this manifest
    std::vector<std::string> searchPaths = _fileUtils->getSearchPaths();
    if (cachedManifest)
    {
        std::vector<std::string> cacheSearchPaths = cachedManifest->getSearchPaths();
        std::vector<std::string> trimmedPaths = searchPaths;
        for (auto path : cacheSearchPaths)
        {
            const auto pos = std::find(trimmedPaths.begin(), trimmedPaths.end(), path);
            if (pos != trimmedPaths.end())
            {
                trimmedPaths.erase(pos);
            }
        }
        _fileUtils->setSearchPaths(trimmedPaths);
    }
    // Load local manifest in app package
    _localManifest->parseFile(_manifestUrl);
    if (cachedManifest)
    {
        // Restore search paths
        _fileUtils->setSearchPaths(searchPaths);
    }
    if (_localManifest->isLoaded())
    {
        cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------44444\n");
        // Compare with cached manifest to determine which one to use
        if (cachedManifest)
        {
            cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------555555\n");
            bool localNewer = _localManifest->versionGreater(cachedManifest, _versionCompareHandle);
            if (localNewer)
            {
                cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------66666\n");
                // Recreate storage, to empty the content
                _fileUtils->removeDirectory(_storagePath);
                _fileUtils->createDirectory(_storagePath);
                CC_SAFE_RELEASE(cachedManifest);
            }
            else
            {
                cocos2d::log("AssetsManagerEx : loadLocalManifest---------------manifestUrl----------77777\n");
                CC_SAFE_RELEASE(_localManifest);
                _localManifest = cachedManifest;
            }
        }
        cocos2d::log("AssetsManagerEx : loadLocalManifest---------------------manifestUrl----------88888\n");
        prepareLocalManifest();
    }

    // Fail to load local manifest
    if (!_localManifest->isLoaded())
    {
        cocos2d::log("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return false;
    }
    initManifests();
    _updateState = State::UNCHECKED;
    return true;
}

bool AssetsManagerEx::loadRemoteManifest(Manifest* remoteManifest)
{
    cocos2d::log("AssetsManagerEx : loadRemoteManifest--------------------\n");
    if (!_inited || _updateState > State::UNCHECKED)
    {
        return false;
    }
    if (!remoteManifest || !remoteManifest->isLoaded())
    {
        return false;
    }
    
    cocos2d::log("AssetsManagerEx : loadRemoteManifest------------------00000\n");
    // Release existing remote manifest
    if (_remoteManifest)
    {
        CC_SAFE_RELEASE(_remoteManifest);
    }
    _remoteManifest = remoteManifest;
    _remoteManifest->retain();
    // Compare manifest version and set state
    if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
    {
        _updateState = State::UP_TO_DATE;
        _fileUtils->removeDirectory(_tempStoragePath);
        cocos2d::log("AssetsManagerEx : loadRemoteManifest------------------1111\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
    }
    else
    {
        cocos2d::log("AssetsManagerEx : loadRemoteManifest------------------22222\n");
        _updateState = State::NEED_UPDATE;
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
    }
    cocos2d::log("AssetsManagerEx : loadRemoteManifest------------------33333\n");
    return true;
}

std::string AssetsManagerEx::basename(const std::string& path) const
{
    size_t found = path.find_last_of("/\\");
    
    if (std::string::npos != found)
    {
        return path.substr(0, found);
    }
    else
    {
        return path;
    }
}

std::string AssetsManagerEx::get(const std::string& key) const
{
    auto it = _assets->find(key);
    if (it != _assets->cend()) {
        return _storagePath + it->second.path;
    }
    else return "";
}

const Manifest* AssetsManagerEx::getLocalManifest() const
{
    return _localManifest;
}

const Manifest* AssetsManagerEx::getRemoteManifest() const
{
    return _remoteManifest;
}

const std::string& AssetsManagerEx::getStoragePath() const
{
    return _storagePath;
}

void AssetsManagerEx::setStoragePath(const std::string& storagePath)
{
    _storagePath = storagePath;
    adjustPath(_storagePath);
    _fileUtils->createDirectory(_storagePath);
    
    _tempStoragePath = _storagePath;
    _tempStoragePath.insert(_storagePath.size() - 1, TEMP_PACKAGE_SUFFIX);
    _fileUtils->createDirectory(_tempStoragePath);
}

void AssetsManagerEx::adjustPath(std::string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
}

bool AssetsManagerEx::decompress(const std::string &zip, bool isTemp)
{
    
    cocos2d::log("AssetsManagerEx : decompress--------------------%s\n", zip.c_str());
    // Find root path for zip file
    size_t pos = zip.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        cocos2d::log("AssetsManagerEx : no root path specified for zip file %s\n", zip.c_str());
        return false;
    }
    const std::string rootPath = zip.substr(0, pos+1);
    
    cocos2d::log("AssetsManagerEx : decompress---------------rootPath-----%s\n", rootPath.c_str());
    // Open the zip file
    unzFile zipfile = unzOpen(FileUtils::getInstance()->getSuitableFOpen(zip).c_str());
    if (! zipfile)
    {
        cocos2d::log("AssetsManagerEx : can not open downloaded zip file %s\n", zip.c_str());
        return false;
    }
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        cocos2d::log("AssetsManagerEx : can not read file global info of %s\n", zip.c_str());
        unzClose(zipfile);
        return false;
    }
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            cocos2d::log("AssetsManagerEx : can not read compressed file info\n");
            unzClose(zipfile);
            return false;
        }
        std::string fullPath = rootPath + fileName;
        
        cocos2d::log("AssetsManagerEx : decompress---------------fullPath-----%s\n", fullPath.c_str());
        if (isTemp)
        {
            fullPath = fullPath + TEMP_SUFFIX;
        }
        cocos2d::log("AssetsManagerEx : decompress---------------fullPath-----%s\n", fullPath.c_str());
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
            //There are not directory entry in some case.
            //So we need to create directory when decompressing file entry
            if ( !_fileUtils->createDirectory(basename(fullPath)) )
            {
                // Failed to create directory
                cocos2d::log("AssetsManagerEx : can not create directory %s\n", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        }
        else
        {
            // Create all directories in advance to avoid issue
            std::string dir = basename(fullPath);
            if (!_fileUtils->isDirectoryExist(dir)) {
                if (!_fileUtils->createDirectory(dir)) {
                    // Failed to create directory
                    cocos2d::log("AssetsManagerEx : can not create directory %s\n", fullPath.c_str());
                    unzClose(zipfile);
                    return false;
                }
            }
            // Entry is a file, so extract it.
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                cocos2d::log("AssetsManagerEx : can not extract file %s\n", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), "wb");
            if (!out)
            {
                cocos2d::log("AssetsManagerEx : can not create decompress destination file %s (errno: %d)\n", fullPath.c_str(), errno);
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            // Write current file content to destinate file.
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    cocos2d::log("AssetsManagerEx : can not read zip file %s, error code is %d\n", fileName, error);
                    fclose(out);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                cocos2d::log("AssetsManagerEx : can not read next file for decompressing\n");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    unzClose(zipfile);
    return true;
}

void AssetsManagerEx::decompressDownloadedZip(const std::string &customId, const std::string &storagePath)
{
    struct AsyncData
    {
        std::string customId;
        std::string zipFile;
        bool succeed;
    };
    
    AsyncData* asyncData = new AsyncData;
    asyncData->customId = customId;
    asyncData->zipFile = storagePath;
    asyncData->succeed = false;
    
    std::function<void(void*)> decompressFinished = [this](void* param) {
        auto dataInner = reinterpret_cast<AsyncData*>(param);
        if (dataInner->succeed)
        {
            fileSuccess(dataInner->customId, dataInner->zipFile);
        }
        else
        {
            std::string errorMsg = "Unable to decompress file " + dataInner->zipFile;
            // Ensure zip file deletion (if decompress failure cause task thread exit anormally)
            _fileUtils->removeFile(dataInner->zipFile);
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS, "", errorMsg);
            fileError(dataInner->customId, errorMsg);
        }
        delete dataInner;
    };
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, decompressFinished, (void*)asyncData, [this, asyncData]() {
        // Decompress all compressed files
        if (decompress(asyncData->zipFile))
        {
            asyncData->succeed = true;
        }
        _fileUtils->removeFile(asyncData->zipFile);
    });
}

void AssetsManagerEx::dispatchUpdateEvent(EventAssetsManagerEx::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    switch (code)
    {
        case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
        case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
        case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
        case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
        case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
        case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
        case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
        case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
            cocos2d::log("AssetsManagerEx : dispatchUpdateEvent------------------0000\n");
            _updateEntry = UpdateEntry::NONE;
            break;
        case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
            break;
        case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
            break;
        case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
            if (_updateEntry == UpdateEntry::CHECK_UPDATE)
            {
                _updateEntry = UpdateEntry::NONE;
            }
            break;
        default:
            break;
    }

    EventAssetsManagerEx* event = new (std::nothrow) EventAssetsManagerEx(_eventName, this, code, assetId, message, curle_code, curlm_code);
    _eventDispatcher->dispatchEvent(event);
    event->release();
}

AssetsManagerEx::State AssetsManagerEx::getState() const
{
    return _updateState;
}

void AssetsManagerEx::downloadVersion()
{
    if (_updateState > State::PREDOWNLOAD_VERSION)
        return;

    std::string versionUrl = getVersionFileUrl();

    if (versionUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_VERSION;
        // Download version file asynchronously
        auto path = _tempVersionPath;
        if (_version_compress)
        {
            path = path + ZIP_SUFFIX;
        }
    
        _downloader->createDownloadFileTask(versionUrl, path, VERSION_ID);
    }
    // No version file found
    else
    {
        cocos2d::log("AssetsManagerEx : No version file found, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
}

void AssetsManagerEx::parseVersion()
{
    cocos2d::log("AssetsManagerEx : parseVersion--------_tempVersionPath----------%s\n", _tempVersionPath.c_str());
    if (_updateState != State::VERSION_LOADED)
        return;

    _remoteManifest->parseVersion(_tempVersionPath);

    cocos2d::log("AssetsManagerEx : parseVersion------------------0000\n");
    if (!_remoteManifest->isVersionLoaded())
    {
        cocos2d::log("AssetsManagerEx : Fail to parse version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else
    {
        if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
        {
            _updateState = State::UP_TO_DATE;
            _fileUtils->removeDirectory(_tempStoragePath);
            cocos2d::log("AssetsManagerEx : parseVersion------------------11111\n");
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;

            // Wait to update so continue the process
            if (_updateEntry == UpdateEntry::DO_UPDATE)
            {
                // dispatch after checking update entry because event dispatching may modify the update entry
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
                _updateState = State::PREDOWNLOAD_MANIFEST;
                downloadManifest();
            }
            else
            {
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
            }
        }
    }
}

void AssetsManagerEx::downloadManifest()
{
    if (_updateState != State::PREDOWNLOAD_MANIFEST)
        return;

    std::string manifestUrl = getManifestFileUrl();

    if (manifestUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_MANIFEST;
        // Download version file asynchronously
        auto path = _tempManifestPath;
        if (_project_compress)
        {
            path = path + ZIP_SUFFIX;
        }
        _downloader->createDownloadFileTask(manifestUrl, path, MANIFEST_ID);
    }
    // No manifest file found
    else
    {
        cocos2d::log("AssetsManagerEx : No manifest file found, check update failed\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST);
        _updateState = State::UNCHECKED;
    }
}

void AssetsManagerEx::parseManifest()
{
    if (_updateState != State::MANIFEST_LOADED)
        return;

    _remoteManifest->parseFile(_tempManifestPath);
    cocos2d::log("AssetsManagerEx : parseManifest------------------00000\n");
    cocos2d::log("AssetsManagerEx : parseManifest---------_tempManifestPath---------%s\n", _tempManifestPath.c_str());
    if (!_remoteManifest->isLoaded())
    {
        cocos2d::log("AssetsManagerEx : Error parsing manifest file, %s", _tempManifestPath.c_str());
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST);
        _updateState = State::UNCHECKED;
    }
    else
    {
        cocos2d::log("AssetsManagerEx : parseManifest------------------1111\n");
        if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
        {
            _updateState = State::UP_TO_DATE;
            _fileUtils->removeDirectory(_tempStoragePath);
            
            cocos2d::log("AssetsManagerEx : parseManifest------------------2222\n");
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);

            if (_updateEntry == UpdateEntry::DO_UPDATE)
            {
                startUpdate();
            }
        }
    }
}

void AssetsManagerEx::prepareUpdate()
{
    cocos2d::log("AssetsManagerEx : prepareUpdate---------------------.\n");
    if (_updateState != State::NEED_UPDATE)
        return;

    // Clean up before update
    _failedUnits.clear();
    _downloadUnits.clear();
    _totalWaitToDownload = _totalToDownload = 0;
    _nextSavePoint = 0;
    _percent = _percentByFile = _sizeCollected = _totalDownloaded = _totalSize = 0;
    _downloadResumed = false;
    _downloadedSize.clear();
    _totalEnabled = false;
    // Temporary manifest exists, previously updating and equals to the remote version, resuming previous download
    if (_tempManifest && _tempManifest->isLoaded() && _tempManifest->isUpdating() && _tempManifest->versionEquals(_remoteManifest))
    {
        _tempManifest->saveToFile(_tempManifestPath);
        _tempManifest->genResumeAssetsList(&_downloadUnits);
        _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
        _downloadResumed = true;
    }
    else
    {
        // Temporary manifest exists, but can't be parsed or version doesn't equals remote manifest (out of date)
        if (_tempManifest)
        {
            cocos2d::log("AssetsManagerEx : prepareUpdate---------------------00000.\n");
            // Remove all temp files
            _fileUtils->removeDirectory(_tempStoragePath);
            CC_SAFE_RELEASE(_tempManifest);
            // Recreate temp storage path and save remote manifest
            _fileUtils->createDirectory(_tempStoragePath);
            _remoteManifest->saveToFile(_tempManifestPath);
        }
        
        // Temporary manifest will be used to register the download states of each asset,
        // in this case, it equals remote manifest.
        _tempManifest = _remoteManifest;
        
        // Check difference between local manifest and remote manifest
        std::unordered_map<std::string, Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
        if (diff_map.size() == 0)
        {
            cocos2d::log("AssetsManagerEx : prepareUpdate---------------------111111.\n");
            updateSucceed();
            return;
        }
        else
        {
            cocos2d::log("AssetsManagerEx : prepareUpdate---------------222222\n");
            // Generate download units for all assets that need to be updated or added
//            std::string packageUrl = getPackageUrl();
            // Preprocessing local files in previous version and creating download folders
            for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
            {
                Manifest::AssetDiff diff = it->second;
                if (diff.type != Manifest::DiffType::DELETED)
                {
                    std::string path = diff.asset.path;
                    DownloadUnit unit;
                    unit.customId = it->first;
                    unit.srcUrl = path;
                    unit.storagePath = _tempStoragePath + path;
                    unit.size = diff.asset.size;
                    _downloadUnits.emplace(unit.customId, unit);
                    _tempManifest->setAssetDownloadState(it->first, Manifest::DownloadState::UNSTARTED);
                }
            }
            // Start updating the temp manifest
            _tempManifest->setUpdating(true);
            // Save current download manifest information for resuming
            _tempManifest->saveToFile(_tempManifestPath);
            cocos2d::log("AssetsManagerEx : prepareUpdate---------------------33333.\n");
            _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
        }
    }
    _updateState = State::READY_TO_UPDATE;
}

void AssetsManagerEx::startUpdate()
{
    cocos2d::log("AssetsManagerEx : startUpdate---------------------.\n");
    if (_updateState == State::NEED_UPDATE)
    {
        cocos2d::log("AssetsManagerEx : startUpdate---------------------00000.\n");
        prepareUpdate();
    }
    if (_updateState == State::READY_TO_UPDATE)
    {
        cocos2d::log("AssetsManagerEx : startUpdate---------------------11111.\n");
        _updateState = State::UPDATING;
        std::string msg;
        if (_downloadResumed)
        {
            cocos2d::log("AssetsManagerEx : startUpdate---------------------22222.\n");
            msg = StringUtils::format("Resuming from previous unfinished update, %d files remains to be finished.", _totalToDownload);
        }
        else
        {
            cocos2d::log("AssetsManagerEx : startUpdate---------------------33333.\n");
            msg = StringUtils::format("Start to update %d files from remote package.", _totalToDownload);
        }
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "", msg);
        batchDownload();
    }
}

void AssetsManagerEx::updateSucceed()
{
    cocos2d::log("AssetsManagerEx : updateSucceed---------------------.\n");
    // Set temp manifest's updating
    _tempManifest->setUpdating(false);
    
    // Every thing is correctly downloaded, do the following
    // 1. rename temporary manifest to valid manifest
    _fileUtils->renameFile(_tempStoragePath, TEMP_MANIFEST_FILENAME, MANIFEST_FILENAME);
    // 2. merge temporary storage path to storage path so that temporary version turns to cached version
    if (_fileUtils->isDirectoryExist(_tempStoragePath))
    {
        // Merging all files in temp storage path to storage path
        std::vector<std::string> files;
        _fileUtils->listFilesRecursively(_tempStoragePath, &files);
        int baseOffset = (int)_tempStoragePath.length();
        std::string relativePath, dstPath;
        for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
        {
            relativePath.assign((*it).substr(baseOffset));
            dstPath.assign(_storagePath + relativePath);
            // Create directory
            if (relativePath.back() == '/')
            {
                _fileUtils->createDirectory(dstPath);
            }
            // Copy file
            else
            {
                if (_fileUtils->isFileExist(dstPath))
                {
                    _fileUtils->removeFile(dstPath);
                }
                _fileUtils->renameFile(*it, dstPath);
            }
        }
        // Remove temp storage path
        _fileUtils->removeDirectory(_tempStoragePath);
    }
    cocos2d::log("AssetsManagerEx : updateSucceed---------------------00000.\n");
    // 3. swap the localManifest
    CC_SAFE_RELEASE(_localManifest);
    _localManifest = _remoteManifest;
    cocos2d::log("AssetsManagerEx : updateSucceed---------------------%s.\n", _storagePath.c_str());
    _localManifest->setManifestRoot(_storagePath);
    _remoteManifest = nullptr;
    // 4. make local manifest take effect
    prepareLocalManifest();
    // 5. Set update state
    _updateState = State::UP_TO_DATE;
    cocos2d::log("AssetsManagerEx : updateSucceed-------------11111\n");
    // 6. Notify finished event
    dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FINISHED);
}

void AssetsManagerEx::checkUpdate()
{
    if (_updateEntry != UpdateEntry::NONE)
    {
        cocos2d::log("AssetsManagerEx::checkUpdate, updateEntry isn't NONE");
        return;
    }

    if (!_inited){
        cocos2d::log("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        cocos2d::log("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    cocos2d::log("AssetsManagerEx : checkUpdate------------------00000\n");
    _updateEntry = UpdateEntry::CHECK_UPDATE;

    switch (_updateState) {
        case State::FAIL_TO_UPDATE:
            _updateState = State::UNCHECKED;
        case State::UNCHECKED:
        case State::PREDOWNLOAD_VERSION:
        {
            downloadVersion();
        }
            break;
        case State::UP_TO_DATE:
        {
            cocos2d::log("AssetsManagerEx : checkUpdate---------------------1111\n");
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
            break;
        case State::NEED_UPDATE:
        {
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
        }
            break;
        default:
            break;
    }
}

void AssetsManagerEx::update()
{
    cocos2d::log("AssetsManagerEx : update---------------------\n");
    if (_updateEntry != UpdateEntry::NONE)
    {
        cocos2d::log("AssetsManagerEx::update, updateEntry isn't NONE");
        return;
    }

    if (!_inited){
        cocos2d::log("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        cocos2d::log("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    _updateEntry = UpdateEntry::DO_UPDATE;

    switch (_updateState) {
        case State::UNCHECKED:
        {
             cocos2d::log("AssetsManagerEx : update---------------------0000\n");
            _updateState = State::PREDOWNLOAD_VERSION;
        }
        case State::PREDOWNLOAD_VERSION:
        {
             cocos2d::log("AssetsManagerEx : update---------------------1111\n");
            downloadVersion();
        }
            break;
        case State::VERSION_LOADED:
        {
             cocos2d::log("AssetsManagerEx : update---------------------2222\n");
            parseVersion();
        }
            break;
        case State::PREDOWNLOAD_MANIFEST:
        {
             cocos2d::log("AssetsManagerEx : update---------------------3333\n");
            downloadManifest();
        }
            break;
        case State::MANIFEST_LOADED:
        {
             cocos2d::log("AssetsManagerEx : update---------------------4444\n");
            parseManifest();
        }
            break;
        case State::FAIL_TO_UPDATE:
        case State::NEED_UPDATE:
        {
             cocos2d::log("AssetsManagerEx : update---------------------5555\n");
            // Manifest not loaded yet
            if (!_remoteManifest->isLoaded())
            {
                 cocos2d::log("AssetsManagerEx : update---------------------66666\n");
                _updateState = State::PREDOWNLOAD_MANIFEST;
                downloadManifest();
            }
            else
            {
                 cocos2d::log("AssetsManagerEx : update---------------------7777\n");
                startUpdate();
            }
        }
            break;
        case State::UP_TO_DATE:
        case State::UPDATING:
        case State::UNZIPPING:
             cocos2d::log("AssetsManagerEx : update---------------------88888\n");
            _updateEntry = UpdateEntry::NONE;
            break;
        default:
            break;
    }
}

void AssetsManagerEx::updateAssets(const DownloadUnits& assets)
{
    if (!_inited){
        cocos2d::log("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
     cocos2d::log("AssetsManagerEx : updateAssets---------------------\n");
    if (_updateState != State::UPDATING && _localManifest->isLoaded() && _remoteManifest->isLoaded())
    {
        _updateState = State::UPDATING;
        _downloadUnits.clear();
        _downloadedSize.clear();
        _percent = _percentByFile = _sizeCollected = _totalDownloaded = _totalSize = 0;
        _totalWaitToDownload = _totalToDownload = (int)assets.size();
        _nextSavePoint = 0;
        _totalEnabled = false;
        if (_totalToDownload > 0)
        {
            cocos2d::log("AssetsManagerEx : updateAssets---------------------0000\n");
            _downloadUnits = assets;
            this->batchDownload();
        }
        else if (_totalToDownload == 0)
        {
            cocos2d::log("AssetsManagerEx : updateAssets---------------------11111.\n");
            onDownloadUnitsFinished();
        }
    }
}

const DownloadUnits& AssetsManagerEx::getFailedAssets() const
{
    return _failedUnits;
}

void AssetsManagerEx::downloadFailedAssets()
{
    cocos2d::log("AssetsManagerEx : Start update %lu failed assets.\n", static_cast<unsigned long>(_failedUnits.size()));
    updateAssets(_failedUnits);
}

void AssetsManagerEx::fileError(const std::string& identifier, const std::string& errorStr, int errorCode, int errorCodeInternal)
{
    auto unitIt = _downloadUnits.find(identifier);
    // Found unit and add it to failed units
    if (unitIt != _downloadUnits.end())
    {
        _totalWaitToDownload--;
        
        DownloadUnit unit = unitIt->second;
        _failedUnits.emplace(unit.customId, unit);
    }
    dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_UPDATING, identifier, errorStr, errorCode, errorCodeInternal);
    _tempManifest->setAssetDownloadState(identifier, Manifest::DownloadState::UNSTARTED);
    
    _currConcurrentTask = MAX(0, _currConcurrentTask-1);
    queueDowload();
}

void AssetsManagerEx::fileSuccess(const std::string &customId, const std::string &storagePath)
{
    // Set download state to SUCCESSED
    _tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::SUCCESSED);
    
    auto unitIt = _failedUnits.find(customId);
    // Found unit and delete it
    if (unitIt != _failedUnits.end())
    {
        // Remove from failed units list
        _failedUnits.erase(unitIt);
    }
    
    unitIt = _downloadUnits.find(customId);
    if (unitIt != _downloadUnits.end())
    {
        // Reduce count only when unit found in _downloadUnits
        _totalWaitToDownload--;
        
        _percentByFile = 100 * (float)(_totalToDownload - _totalWaitToDownload) / _totalToDownload;
        // Notify progression event
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "");
    }
    // Notify asset updated event
    dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ASSET_UPDATED, customId);
    
    _currConcurrentTask = MAX(0, _currConcurrentTask-1);
    queueDowload();
}

void AssetsManagerEx::onError(const network::DownloadTask& task,
                              int errorCode,
                              int errorCodeInternal,
                              const std::string& errorStr)
{
    // Skip version error occurred
    if (task.identifier == VERSION_ID)
    {
        cocos2d::log("AssetsManagerEx : Fail to download version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else if (task.identifier == MANIFEST_ID)
    {
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST, task.identifier, errorStr, errorCode, errorCodeInternal);
        _updateState = State::FAIL_TO_UPDATE;
    }
    else
    {
        fileError(task.identifier, errorStr, errorCode, errorCodeInternal);
    }
}

void AssetsManagerEx::onProgress(double total, double downloaded, const std::string& /*url*/, const std::string &customId)
{
    if (customId == VERSION_ID || customId == MANIFEST_ID)
    {
        _percent = 100 * downloaded / total;
        // Notify progression event
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, customId);
        return;
    }
    else
    {
        // Calcul total downloaded
        bool found = false;
        _totalDownloaded = 0;
        for (auto it = _downloadedSize.begin(); it != _downloadedSize.end(); ++it)
        {
            if (it->first == customId)
            {
                it->second = downloaded;
                found = true;
            }
            _totalDownloaded += it->second;
        }
        // Collect information if not registed
        if (!found)
        {
            // Set download state to DOWNLOADING, this will run only once in the download process
            _tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::DOWNLOADING);
            // Register the download size information
            _downloadedSize.emplace(customId, downloaded);
            // Check download unit size existance, if not exist collect size in total size
            if (_downloadUnits[customId].size == 0)
            {
                _totalSize += total;
                _sizeCollected++;
                // All collected, enable total size
                if (_sizeCollected == _totalToDownload)
                {
                    _totalEnabled = true;
                }
            }
        }
        
        if (_totalEnabled && _updateState == State::UPDATING)
        {
            float currentPercent = 100 * _totalDownloaded / _totalSize;
            // Notify at integer level change
            if ((int)currentPercent != (int)_percent) {
                _percent = currentPercent;
                // Notify progression event
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, customId);
            }
        }
    }
}

void AssetsManagerEx::onSuccess(const std::string &/*srcUrl*/, const std::string &storagePath, const std::string &customId)
{
    if (customId == VERSION_ID)
    {
        _updateState = State::VERSION_LOADED;
        if (_version_compress)
        {
            cocos2d::log("AssetsManagerEx : onSuccess-------VERSION_ID storagePath-------%s\n",storagePath.c_str());
            decompress(storagePath);
        }
        
        parseVersion();
    }
    else if (customId == MANIFEST_ID)
    {
        _updateState = State::MANIFEST_LOADED;
        if (_project_compress)
        {
            cocos2d::log("AssetsManagerEx : onSuccess-------MANIFEST_ID storagePath-------%s\n",storagePath.c_str());
            decompress(storagePath, true);
        }
        
        parseManifest();
    }
    else
    {
        bool ok = true;
        auto &assets = _remoteManifest->getAssets();
        auto assetIt = assets.find(customId);
        if (assetIt != assets.end())
        {
            Manifest::Asset asset = assetIt->second;
            if (_verifyCallback != nullptr)
            {
                ok = _verifyCallback(storagePath, asset);
            }
        }
        
        if (ok)
        {
            bool compressed = assetIt != assets.end() ? assetIt->second.compressed : false;
            if (compressed)
            {
                decompressDownloadedZip(customId, storagePath);
            }
            else
            {
                fileSuccess(customId, storagePath);
            }
        }
        else
        {
            fileError(customId, "Asset file verification failed after downloaded");
        }
    }
}

void AssetsManagerEx::destroyDownloadedVersion()
{
    _fileUtils->removeDirectory(_storagePath);
    _fileUtils->removeDirectory(_tempStoragePath);
}

void AssetsManagerEx::batchDownload()
{
    _queue.clear();
    for(auto iter : _downloadUnits)
    {
        const DownloadUnit& unit = iter.second;
        if (unit.size > 0)
        {
            _totalSize += unit.size;
            _sizeCollected++;
        }
        
        _queue.push_back(iter.first);
    }
    // All collected, enable total size
    if (_sizeCollected == _totalToDownload)
    {
        _totalEnabled = true;
    }
    
    queueDowload();
}

void AssetsManagerEx::queueDowload()
{
    if (_totalWaitToDownload == 0)
    {
        cocos2d::log("AssetsManagerEx : queueDowload---------------------.\n");
        this->onDownloadUnitsFinished();
        return;
    }
    
    std::string packageUrl = getPackageUrl();
    while (_currConcurrentTask < _maxConcurrentTask && _queue.size() > 0)
    {
        std::string key = _queue.back();
        _queue.pop_back();
        
        _currConcurrentTask++;
        DownloadUnit& unit = _downloadUnits[key];
        _fileUtils->createDirectory(basename(unit.storagePath));
        _downloader->createDownloadFileTask(packageUrl + unit.srcUrl, unit.storagePath, unit.customId);
        
        _tempManifest->setAssetDownloadState(key, Manifest::DownloadState::DOWNLOADING);
    }
    if (_percentByFile / 100 > _nextSavePoint)
    {
        // Save current download manifest information for resuming
        _tempManifest->saveToFile(_tempManifestPath);
        _nextSavePoint += SAVE_POINT_INTERVAL;
    }
}

void AssetsManagerEx::onDownloadUnitsFinished()
{
    // Finished with error check
    if (_failedUnits.size() > 0)
    {
        // Save current download manifest information for resuming
        _tempManifest->saveToFile(_tempManifestPath);
    
        _updateState = State::FAIL_TO_UPDATE;
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FAILED);
    }
    else if (_updateState == State::UPDATING)
    {
        cocos2d::log("AssetsManagerEx : queueDowload---------------------.\n");
        updateSucceed();
    }
}

const std::string& AssetsManagerEx::getPackageUrl() const
{
    return _packageUrl;
}

const std::string& AssetsManagerEx::getManifestFileUrl() const
{
    return _remoteManifestUrl;
}

const std::string& AssetsManagerEx::getVersionFileUrl() const
{
    return _remoteVersionUrl;
}

void AssetsManagerEx::setPackageUrl(const std::string url)
{
    _packageUrl = url;
    if (_packageUrl.size() > 0 && _packageUrl[_packageUrl.size() - 1] != '/')
    {
        _packageUrl.append("/");
    }
}

void AssetsManagerEx::setManifestFileUrl(const std::string url)
{
    _remoteManifestUrl = url;
}

void AssetsManagerEx::setVersionFileUrl(const std::string url)
{
    _remoteVersionUrl = url;
}

void AssetsManagerEx::setProjectCompress(bool flag)
{
    _project_compress = flag;
}
void AssetsManagerEx::setVersionCompress(bool flag)
{
    _version_compress = flag;
}

NS_CC_EXT_END
