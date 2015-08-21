#ifndef LOGOACTIONTIMELINENODE_H
#define LOGOACTIONTIMELINENODE_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include <string>
#include "Sources/GAF.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
class LogoActionTimelineNode : public ActionTimelineNode
{
    //由于动画实现的方式众多，比如gaf。csb等方式。因此这个类应该设计成接口
public:
    static const int STATE_NORMAL;
    static const int STATE_MOUSE_OPEN ;
    static const int STATE_MOUSE_CLOSE;
        static const int STATE_MOUSE_WORKING;
    LogoActionTimelineNode();
    static int currentState;
    static LogoActionTimelineNode* create();
    void nihao(int a = 1);
    void performWorkingAnim(bool loop = false);
    void performTongueAnim(bool loop = false);
    void performMouseOpenAnim(bool loop = false);
    void performMouseCloseAnim(bool loop = false);
    void performNormalAnim(bool loop =false);

    void performMouseAnim(float percent);
    void performWorkingAnim(float percent);
    void performTongueAnim(float percent);

    bool init(cocos2d::Node* root, ActionTimeline* action);

    virtual void setRoot(cocos2d::Node* root);
    virtual cocos2d::Node* getRoot();
    virtual void setActionTimeline(ActionTimeline* action);
    virtual ActionTimeline* getActionTimeline();
private:
    //加载gaf动画并控制动画
    static gaf::GAFObject* _gafObj;
protected:
    
    cocos2d::Node* _root;
    ActionTimeline* _action;
};

#endif // LOGOACTIONTIMELINENODE_H
