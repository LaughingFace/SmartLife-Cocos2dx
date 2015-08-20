#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "modelmanager.h"


#define CLASS_NAME "org/cocos2dx/cpp/NativeModelManager"
using namespace cocos2d;

extern"C"
{
	ModelManager* mm = ModelManager::getInstance();
	void Java_org_cocos2dx_cpp_NativeModelManager_onLine(JNIEnv*env,jobject thiz)
	{
           log("onLine Called by java..................");
				mm->onLine();
	}

void Java_org_cocos2dx_cpp_NativeModelManager_offLine(JNIEnv*env,jobject thiz)
	{
           log("offLine Called by java..................");
				mm->offLine();
	}

	void Java_org_cocos2dx_cpp_NativeModelManager_onModelStart(JNIEnv*env,jobject thiz)
	{
           log("onModelStart Called by java..................");
				mm->onModelStart();
	}

void Java_org_cocos2dx_cpp_NativeModelManager_onProcessing(JNIEnv*env,jobject thiz)
	{
           log("onProcessing by java..................");
				mm->onProcessing();
	}

void Java_org_cocos2dx_cpp_NativeModelManager_onFinish(JNIEnv*env,jobject thiz)
	{
           log("onFinish by java..................");
				mm->onFinish();
	}

void Java_org_cocos2dx_cpp_NativeModelManager_onInterupt(JNIEnv*env,jobject thiz)
	{
           log("onInterupt by java..................");
				mm->onInterupt();
	}

void Java_org_cocos2dx_cpp_NativeModelManager_faillOnStart(JNIEnv*env,jobject thiz)
	{
           log("faillOnStart by java..................");
				mm->faillOnStart();
	}
}
