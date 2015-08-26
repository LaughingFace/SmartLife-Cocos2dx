#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"
#include "DreamlikeAnim/LogoAnim.h"
//#include "ElasticRope/ElasticRope.h"

using namespace cocos2d;
using namespace cocostudio::timeline;
class ModelManager
{
private:
    ModelManager(){}
    static ModelManager* instance;
    static Node* _rootNode;
    static Node* _logo_normal;
    static b2World* _world;
public:
    static ModelManager * getInstance()
    {
        if(!ModelManager::instance)  //判断是否第一次调用
           ModelManager::instance = new ModelManager();
        return instance;
    }
    static void setAction(Node* rootNode,void* rope,LogoAnim* laughingMan2);
    static void setWorld(b2World* world);
    void offLine() ;
     void onLine() ;
    void onModelStart() ;
    void onProcessing() ;
    void onFinish() ;
     void onInterupt() ;
    void faillOnStart() ;

    void startStandard();
    void startDryoff();
    void callJavaFun(const char *className,const char *methodName,const char *paramCode);



};

#endif // MODELMANAGER_H
