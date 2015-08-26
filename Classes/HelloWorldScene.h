#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "modelmanager.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoStudio.h"
#include "ElasticRope/ElasticRope.h"
#include "logoactiontimelinenode.h"
#include "DreamlikeAnim/AnimFactory.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace ElasticRopeBox2d;
class HelloWorld :
public cocos2d::Layer
,public ElasticRopeCallback
{
    private :
    //view config;
    Vec2 _fanPostion;
    Vec2 _laughingManPostion;
    Vec2 _elasticRopePostion;
    Vec2 _washingBirthplacePosition;
    //view
    Sprite* _title;//标题栏。
    Sprite* _washing;;//洗涤物。
    ElasticRope* _elasticRope;//橡皮筋效果控件。
    WarmSwitchAnim* _warmSwitch;//风扇开关。
    LogoAnim* _laughingMan;//笑人动画控件。
    Size _visibleSize;//屏幕可是区域大小。
    EventListenerTouchOneByOne* washingListener ;
    void initView();
    void loadViewConfig();
    void onLogoAnimEnd(gaf::GAFObject* obj);
public:
  
    void onUpdatePosition(Vec2* position);
    void onData(void* data);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float delta);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
