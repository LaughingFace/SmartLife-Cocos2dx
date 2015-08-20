#include "logoactiontimelinenode.h"

 const int LogoActionTimelineNode::STATE_NORMAL = 0 ;
 const int LogoActionTimelineNode::STATE_MOUSE_OPEN = 1 ;
 const int LogoActionTimelineNode::STATE_MOUSE_CLOSE = 2;
const int LogoActionTimelineNode::STATE_MOUSE_WORKING = 6;
const float TimeSpeed = 3.5f;
Sprite* LogoActionTimelineNode::_normalSprite;
int LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_NORMAL;
void LogoActionTimelineNode::performMouseOpenAnim(bool loop){
    _normalSprite->setVisible(false);
    this->getActionTimeline()->setTimeSpeed(TimeSpeed);
    this->getActionTimeline ()->gotoFrameAndPlay (305,369,loop);

}
void LogoActionTimelineNode::performMouseCloseAnim(bool loop){
    _normalSprite->setVisible(false);

    this->getActionTimeline()->setTimeSpeed(TimeSpeed);
    log("aaa%d",this->getActionTimeline()->getDuration());
     this->getActionTimeline ()->gotoFrameAndPlay (370,424,loop);
    scheduleOnce(schedule_selector(LogoActionTimelineNode::callback),
                0.6f);
}
void LogoActionTimelineNode::performWorkingAnim(bool loop){
    
    _normalSprite->setVisible(false);
this->getActionTimeline()->setTimeSpeed(1.0f);
        this->getActionTimeline ()->gotoFrameAndPlay (0,214,loop);
    currentState == STATE_MOUSE_WORKING;
    scheduleOnce(schedule_selector(LogoActionTimelineNode::callback2),
                 1.0f);
}

void LogoActionTimelineNode::performTongueAnim(bool loop){
    _normalSprite->setVisible(false);

    this->getActionTimeline()->setTimeSpeed(TimeSpeed);

        this->getActionTimeline ()->gotoFrameAndPlay (214,304,loop);
    scheduleOnce(schedule_selector(LogoActionTimelineNode::callback),
                 1.0f);

}

void LogoActionTimelineNode::onFrameEvent(Frame* frame)
{
    log("a");
}
void LogoActionTimelineNode::performMouseAnim(float percent){
    int frame = (int)120*percent+305;
    CCLog("frame:::::%d",frame);
    this->getActionTimeline ()->gotoFrameAndPause (frame);
}

void LogoActionTimelineNode::performWorkingAnim(float percent){
    int frame = (int)214 * percent;
        this->getActionTimeline ()->gotoFrameAndPause (frame);
}

void LogoActionTimelineNode::performTongueAnim(float percent){
    int frame = (int)91 * percent+214;
        this->getActionTimeline ()->gotoFrameAndPause (frame);
    
}

LogoActionTimelineNode* LogoActionTimelineNode::create()
{
    auto root = CSLoader::createNode ("logo_anim.csb");
    auto action = CSLoader::createTimeline ("logo_anim.csb");
    LogoActionTimelineNode* object = new (std::nothrow) LogoActionTimelineNode();
    if (object && object->init(root, action))
    {
        object->autorelease();
        _normalSprite = Sprite::create("logo_normal.png");
        object->addChild(_normalSprite,100);
        
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
    _root = root;
    _action = action;

    if(_root)
    {
        _root->removeFromParent();
        addChild(_root);
    }
    this->getActionTimeline()->setFrameEventCallFunc(CC_CALLBACK_1(LogoActionTimelineNode::onFrameEvent,this));
    this->runAction (this->getActionTimeline ());
    return true;
}
void LogoActionTimelineNode::callback(float delta)
{
    if (currentState != STATE_MOUSE_WORKING)
    _normalSprite->setVisible(true);
    log("aaa");
}
void LogoActionTimelineNode::callback2(float delta)
{
            _normalSprite->setVisible(false);
    log("aaa");
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

