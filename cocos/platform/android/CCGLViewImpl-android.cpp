/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/CCGLViewImpl-android.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "platform/android/jni/JniHelper.h"
#include "CCGL.h"

#include <stdlib.h>
#include <android/log.h>

// <EGL/egl.h> exists since android 2.3
#include <EGL/egl.h>
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

void initExtensions() {
     glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
     glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
     glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
}

NS_CC_BEGIN

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName)
{
    auto ret = new GLViewImpl();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl::GLViewImpl()
{
    initExtensions();
}

GLViewImpl::~GLViewImpl()
{

}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
    return true;
}


bool GLViewImpl::isOpenGLReady()
{
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

void GLViewImpl::end()
{
    JniHelper::callStaticVoidMethod("org/cocos2dx/lib/Cocos2dxHelper", "terminateProcess");
}

void GLViewImpl::swapBuffers()
{
}

void GLViewImpl::setIMEKeyboardState(bool bOpen)
{
    if (bOpen) {
        JniHelper::callStaticVoidMethod("org/cocos2dx/lib/Cocos2dxGLSurfaceView", "openIMEKeyboard");
    } else {
        JniHelper::callStaticVoidMethod("org/cocos2dx/lib/Cocos2dxGLSurfaceView", "closeIMEKeyboard");
    }
}


Rect GLViewImpl::getSafeAreaRect() const
{
    static int notch_height = -1;

    Rect safe_area_rect = getVisibleRect();

    if (-1 == notch_height)
    {
        notch_height = JniHelper::callStaticIntMethod("org/cocos2dx/lib/Cocos2dxActivity", "GetNotchHeight");
    }

    if (notch_height > 0)
    {
        safe_area_rect.origin.x = notch_height;
        safe_area_rect.size.width -= notch_height * 2;
    }

    return safe_area_rect;
}


NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
