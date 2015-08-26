#include "modelmanager.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif
#include "HelloworldSceneViewConfig.h"
#include "ElasticRope/ElasticRope.h"
ModelManager* ModelManager::instance;
 ActionTimelineNode* ModelManager::_face;
 ActionTimelineNode* ModelManager::_working;
 ActionTimelineNode* ModelManager::_tongue;
  ActionTimelineNode* ModelManager::_mouse_close;
 Node* ModelManager::_logo_normal;
 Node* ModelManager::_rootNode;
 b2World* ModelManager::_world;
static void* _elasticRope;
static LogoActionTimelineNode* laughingMan;
int tag = 0;
void ModelManager::setAction(Node* rootNode,void* elasticRope,LogoActionTimelineNode* laughingMan2)
{
        _rootNode = rootNode;
    _elasticRope = elasticRope;
    laughingMan = laughingMan2;
       tag = 1;
}

void ModelManager::onLine ()
{
    log("<<<<<<<<<< onLine >>>>>>>>>>>");
}

void ModelManager::offLine()
{
    log("<<<<<<<<<< offLine >>>>>>>>>>>");
}
LogoActionTimelineNode* object;
void ModelManager::onModelStart()
{
    log("<<<<<<<<<< onModelStart >>>>>>>>>>>");
    if (tag == 1)
    {
//        LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_MOUSE_OPEN;
//        laughingMan->performWorkingAnim(true);
        
        viewConfig::working = 1;
        
    }

}

void ModelManager::onProcessing()
{
    log("<<<<<<<<<< onProcessing >>>>>>>>>>>");
}
void ModelManager::setWorld(b2World *world){
    _world = world;
}

void ModelManager::onFinish()
{
    log("<<<<<<<<<< onFinish >>>>>>>>>>>");
    LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_NORMAL;
    laughingMan->performTongueAnim(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto a = (ElasticRopeBox2d::ElasticRope*)(_elasticRope);
    
    a->createB2body(Vec2(visibleSize.width/2,visibleSize.height*viewConfig::LAUGHINF_MAN_Y),1);
}

void ModelManager::onInterupt()
{
    log("<<<<<<<<<< onInterupt >>>>>>>>>>>");
}

void ModelManager::faillOnStart()
{
    log("<<<<<<<<<< faillOnStart >>>>>>>>>>>");
}

void ModelManager::startStandard ()
{
    callJavaFun ("org.cocos2dx.cpp.NativeModelManager","startStandard","()V");
}

void ModelManager::startDryoff ()
{
    callJavaFun ("org.cocos2dx.cpp.NativeModelManager","startDryoff","()V");
}

void ModelManager::callJavaFun (const char *className, const char *methodName,const char *paramCode)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    typedef struct JniMethodInfo_
//    {
//        JNIEnv *    env;
//        jclass      classID;
//        jmethodID   methodID;
//    } JniMethodInfo;

    JniMethodInfo info;
    //getStaticMethodInfo判断java定义的静态函数是否存在，返回bool
    bool ret = JniHelper::getStaticMethodInfo(info,className,methodName,paramCode);
    if(ret)
    {
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        info.env->CallStaticVoidMethod(info.classID,info.methodID);
    }

#endif
}

