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
#include "I18nEx.h"
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

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

#define DEFAULT_CONNECTION_TIMEOUT 45

#define SAVE_POINT_INTERVAL 0.1

// Implementation of I18nEx

//I18nEx* I18nEx::getInstance()
//{
//    if (s_sharedI18nEx == nullptr)
//    {
//        s_sharedI18nEx = new (std::nothrow) I18nEx();
//        if(!s_sharedI18nEx->init())
//        {
//            delete s_sharedI18nEx;
//            s_sharedI18nEx = nullptr;
//            CCLOG("ERROR: Could not init CCFileUtilsApple");
//        }
//    }
//    return s_sharedI18nEx;
//}

I18nEx::I18nEx(const std::string& language, const std::string& languageFile)
: _languageFile("")
, _language("")
, _fileUtils(nullptr)
, _out(nullptr)
{
    init(language, languageFile);
}

bool I18nEx::init(const std::string& language, const std::string& languageFile)
{
    _languageFile = languageFile;
    _language = language;
    
    _fileUtils = FileUtils::getInstance();
    if (!_fileUtils->isFileExist(_languageFile))
    {
        return false;
    }
    
    // Create a file to store current file.
    do
    {
        if (_out)
        {
            fclose(_out);
            _out = nullptr;
        }
        
        // Read the file from hardware
        auto path = FileUtils::getInstance()->fullPathForFilename(_languageFile);
        if (FileUtils::getInstance()->isFileExist(path))
        {
            _out = fopen(FileUtils::getInstance()->getSuitableFOpen(_languageFile).c_str(), "rb");
        }
        else
        {
            CCLOG("NO FILE FOR %s", path.c_str());
        }
        CC_BREAK_IF(!_out);
        return true;
    } while (0);
    
    return false;
}

I18nEx::~I18nEx()
{
    if (_out)
    {
        fclose(_out);
        _out = nullptr;
    }
}

I18nEx* I18nEx::create(const std::string& language, const std::string& languageFile)
{
    I18nEx* ret = new (std::nothrow) I18nEx(language, languageFile);
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


std::string I18nEx::t(int offset)
{
    char mystring [200];
    if (_out)
    {
        fseek ( _out, offset, SEEK_SET );
        if ( fgets (mystring , 200 , _out) != NULL )
        {
            return mystring;
        }
        
        CCLOG("NO STRING IN FILE OFFSET: %d", offset);
    }
    
    CCLOG("NO OPEN FILE");
    return "";
}

const std::string& I18nEx::getLanguageFile() const
{
    return _languageFile;
}

const std::string& I18nEx::getLanguage() const
{
    return _language;
}

void I18nEx::setLanguageFile(const std::string languageFile)
{
    if (_languageFile != languageFile)
    {
        if (_out)
        {
            fclose(_out);
            _out = nullptr;
        }
        
        if (!init(_language, _languageFile))
        {
            CCLOG("Can not open file %s\n", _languageFile.c_str());
        }
    }
    _languageFile = languageFile;
}

void I18nEx::setLanguage(const std::string language)
{
    _language = language;
}

NS_CC_EXT_END
