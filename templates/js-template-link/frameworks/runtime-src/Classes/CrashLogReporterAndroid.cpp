#include "CrashLogReporter.h"


#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/CCApplication-android.h"
#include "platform/android/CCGLViewImpl-android.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventType.h"
#include "base/CCEventDispatcher.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccGLStateCache.h"
#include "2d/CCDrawingPrimitives.h"
#include "platform/android/jni/JniHelper.h"
#include "network/CCDownloader-android.h"
#include <android/log.h>
#include <android/api-level.h>
#include <jni.h>


using namespace cocos2d;

extern "C"
{

void CrashLogReporter::UploadLog()
{
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/javascript/CrashLogReporter", "UploadLog", "()V");
    if (isHave)
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }

    minfo.env->DeleteLocalRef(minfo.classID);
}

}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

