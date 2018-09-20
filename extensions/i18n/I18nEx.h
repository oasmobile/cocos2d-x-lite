/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __I18nEx__
#define __I18nEx__

#include <string>
#include <unordered_map>
#include <vector>

#include "base/CCEventDispatcher.h"
#include "platform/CCFileUtils.h"
#include "network/CCDownloader.h"

#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

#include "json/document-wrapper.h"


NS_CC_EXT_BEGIN

class CC_EX_DLL I18nEx : public Ref
{
public:

    /**
     *  Gets the instance of I18nEx.
     */
//    static I18nEx* getInstance();
    static I18nEx* create(const std::string& language, const std::string& languageFile);
    
    std::string t(int offset);
    
    const std::string& getLanguageFile() const;

    const std::string& getLanguage() const;
    
    void setLanguageFile(const std::string);
    
    void setLanguage(const std::string);
    
CC_CONSTRUCTOR_ACCESS:
    
    I18nEx(const std::string& language, const std::string& languageFile);
    
    virtual ~I18nEx();
    
protected:
    
    bool init(const std::string& language = "", const std::string& languageFile = "");
    
private:
    
    std::string _languageFile;

    std::string _language;
    
    FILE *_out;
    //! Reference to the global file utils
    FileUtils *_fileUtils;
    
    /**
     *  The singleton pointer of FileUtils.
     */
    static I18nEx* s_sharedI18nEx;
};

NS_CC_EXT_END

#endif /* defined(__I18nEx__) */
