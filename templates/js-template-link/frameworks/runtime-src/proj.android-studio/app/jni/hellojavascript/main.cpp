#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/CCFileUtils-android.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include <android/log.h>
#if PACKAGE_AS
#include "PluginJniHelper.h"
#include "SDKManager.h"
#endif

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;
#if PACKAGE_AS
using namespace anysdk::framework;
#endif

void cocos_android_app_init (JNIEnv* env) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
#if PACKAGE_AS
    JavaVM* vm;
    env->GetJavaVM(&vm);
    PluginJniHelper::setJavaVM(vm);
#endif
}

extern "C"
{
	void Java_org_cocos2dx_javascript_SDKWrapper_nativeLoadAllPlugins(JNIEnv*  env, jobject thiz)
	{
#if PACKAGE_AS
    	SDKManager::getInstance()->loadAllPlugins();
#endif
	}

    bool Java_org_cocos2dx_javascript_AppActivity_isObbfileExist(JNIEnv*  env, jobject thiz)
    {
        CCLOG("get apk path (%s)", getApkPath());
        return (nullptr != FileUtilsAndroid::getObbFile());
    }

    bool Java_org_cocos2dx_javascript_AppActivity_initFileUtils(JNIEnv*  env, jobject thiz)
    {
        LOGD("----------------------  init file utils");
        FileUtils::getInstance();
    }

    void Java_org_cocos2dx_javascript_AppActivity_update_status(JNIEnv*  env, jobject thiz)
    {
    }

    bool Java_org_cocos2dx_javascript_AppActivity_update_progress(JNIEnv*  env, jobject thiz)
    {
    }

    bool Java_org_cocos2dx_javascript_AppActivity_start_game(JNIEnv*  env, jobject thiz)
    {
    }
}
