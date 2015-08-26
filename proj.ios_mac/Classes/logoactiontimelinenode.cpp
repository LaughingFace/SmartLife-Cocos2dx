#include "logoactiontimelinenode.h"

 const int LogoActionTimelineNode::STATE_NORMAL = 0 ;
 const int LogoActionTimelineNode::STATE_MOUSE_OPEN = 1 ;
 const int LogoActionTimelineNode::STATE_MOUSE_CLOSE = 2;
const int LogoActionTimelineNode::STATE_MOUSE_WORKING = 6;
const float TimeSpeed = 3.5f;
int LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_NORMAL;
gaf::GAFObject* LogoActionTimelineNode::_gafObj;
void LogoActionTimelineNode::performMouseOpenAnim(bool loop){
    
        _gafObj->playSequence("openmouse", loop);
}
void LogoActionTimelineNode::performMouseCloseAnim(bool loop){
    _gafObj->playSequence("closemouse", loop);

}
void LogoActionTimelineNode::performWorkingAnim(bool loop){
    
    _gafObj->playSequence("working", loop);
}

void LogoActionTimelineNode::performTongueAnim(bool loop){
    _gafObj->playSequence("eat", loop);
    _gafObj->setAnimationFinishedPlayDelegate([loop](gaf::GAFObject* gafObject){
        _gafObj->playSequence("normal", false);
        _gafObj->setAnimationFinishedPlayDelegate(nullptr);
    });
}

void LogoActionTimelineNode::performMouseAnim(float percent){

}

void LogoActionTimelineNode::performWorkingAnim(float percent){
 
}

void LogoActionTimelineNode::performTongueAnim(float percent){
    
}
void LogoActionTimelineNode::performNormalAnim(bool loop)
{
    _gafObj->playSequence("normal", loop);
}
LogoActionTimelineNode* LogoActionTimelineNode::create()
{
    
    LogoActionTimelineNode* object = new (std::nothrow) LogoActionTimelineNode();
    if (object)
    {
        object->autorelease();

        auto asset = gaf::GAFAsset::create("LogoFaceAnim/LogoFaceAnim.gaf");
        _gafObj = asset->createObject();
        _gafObj->start();
        
        _gafObj->setAnchorPoint(Vec2(0.5f,0.5f));
        object->performNormalAnim();
        object->addChild(_gafObj);
        
        return object;
    }
    CC_SAFE_DELETE(object);
    
    return nullptr;
}
LogoActionTimelineNode::LogoActionTimelineNode()
: _root(nullptr)
, _action(nullptr)
{
}

bool LogoActionTimelineNode::init(Node* root, ActionTimeline* action)
{
//    _root = root;
//    _action = action;
//
//    if(_root)
//    {
//        _root->removeFromParent();
//        addChild(_root);
//    }
//    this->getActionTimeline()->setFrameEventCallFunc(CC_CALLBACK_1(LogoActionTimelineNode::onFrameEvent,this));
//    this->runAction (this->getActionTimeline ());
    return true;
}

void LogoActionTimelineNode::setRoot(cocos2d::Node* root)
{
    _root = root;
}
cocos2d::Node* LogoActionTimelineNode::getRoot()
{
    return _root;
}

void LogoActionTimelineNode::setActionTimeline(ActionTimeline* action)
{
    _action = action;
}
ActionTimeline* LogoActionTimelineNode::getActionTimeline()
{
    return _action;
}

