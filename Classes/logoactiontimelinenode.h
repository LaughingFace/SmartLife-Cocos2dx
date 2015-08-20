#ifndef LOGOACTIONTIMELINENODE_H
#define LOGOACTIONTIMELINENODE_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

class LogoActionTimelineNode : public ActionTimelineNode
{
public:
    static const int STATE_NORMAL;
    static const int STATE_MOUSE_OPEN ;
    static const int STATE_MOUSE_CLOSE;
        static const int STATE_MOUSE_WORKING;
    LogoActionTimelineNode();
    static Sprite* _normalSprite;
    static int currentState;
    static LogoActionTimelineNode* create();
   // bool init(cocos2d::Node* root, ActionTimeline* action);

    void performWorkingAnim(bool loop);
    void performTongueAnim(bool loop);
    void performMouseOpenAnim(bool loop);
    void performMouseCloseAnim(bool loop);

    void performMouseAnim(float percent);
    void performWorkingAnim(float percent);
    void performTongueAnim(float percent);

    bool init(cocos2d::Node* root, ActionTimeline* action);

    virtual void setRoot(cocos2d::Node* root);
    virtual cocos2d::Node* getRoot();
    void callback(float d);
    void callback2(float dd);
    virtual void setActionTimeline(ActionTimeline* action);
    virtual ActionTimeline* getActionTimeline();
void onFrameEvent(Frame* frame);
protected:
    cocos2d::Node* _root;
    ActionTimeline* _action;
};

#endif // LOGOACTIONTIMELINENODE_H
