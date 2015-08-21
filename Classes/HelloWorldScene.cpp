#include "HelloWorldScene.h"
#include "logoanimationloader.h"
#include "HelloworldSceneViewConfig.h"
#include "LocationAnalyst.h"

Scene* HelloWorld::createScene()
{
    //aa
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

ActionTimeline*  fengshanAnimation;
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //init configinfo;
    loadViewConfig();
    
    initView();
    
    
    closeItem->setPosition(Vec2(origin.x + _visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    // 3. add your codes below...
    //add titlebar

    //风扇停止。
    auto fansanListener = EventListenerTouchOneByOne::create();
    fansanListener->onTouchBegan = [this](Touch* touch,Event* event){
        if(event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()))
            {
            if(this->_fan->getActionTimeline()->isPlaying ()){
                this->_fan->getActionTimeline()->gotoFrameAndPause (0);
            }
            else
            {
                this->_fan->getActionTimeline()->gotoFrameAndPlay (0);
            }
            return true;
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority (fansanListener,_fan->getChildByName("background"));
    
    //洗涤物触摸监听。
    washingListener = EventListenerTouchOneByOne::create();
    washingListener->onTouchBegan = [this](Touch* t,Event* e)
    {
        if (this->_washing && this->_washing->getBoundingBox().containsPoint(t->getLocation())){
             log("on touch began");
            LocationAnalyst::isTouch = true;
            LocationAnalyst::state = WASHING_NOTHING;
            return true;
        }
       
        return false;
    };
    washingListener->onTouchMoved = [this](Touch* t,Event* e)
    {
        
       
        
        //位置检测，
        switch(LocationAnalyst::doWhat(t->getLocation(),0))
        {
            case WASHING_CHANGE:
                _elasticRope->style1();
                if (LogoActionTimelineNode::currentState == LogoActionTimelineNode::STATE_MOUSE_OPEN)
                {
                    
                    this->_laughingMan->performMouseCloseAnim(false);
                    LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_NORMAL;
                }
                break;
            case WASHING_SELECT:
                if (LogoActionTimelineNode::currentState ==LogoActionTimelineNode::STATE_NORMAL)
                {
                    _elasticRope->style2();
                    this->_laughingMan->performMouseOpenAnim(false);
                    LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_MOUSE_OPEN;
                }
                
                break;
            default:
                return;
        }
        //拖动 前台元素与物理元素位置。
        Vec2 vec2 = Vec2(this->_visibleSize.width/2,t->getLocation().y);
        this->_elasticRope->getMovePermission()->move(vec2);
    };
    washingListener->onTouchEnded = [this](Touch* t,Event* e)
    {
        this->_elasticRope->getMovePermission()->endMove();
        log("on touch ended");
        switch(LocationAnalyst::doWhat(t->getLocation(),0))
        {
            case WASHING_CHANGE:
                LocationAnalyst::state = LocationAnalyst::STATE_REBIRTH;
                LocationAnalyst::isTouch = false;
                break;
            case WASHING_SELECT:
                LocationAnalyst::state = LocationAnalyst::STATE_FOOD;
                LocationAnalyst::isTouch = false;
                break;
        }
        
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(washingListener, this);
    //后台服务
         ModelManager::getInstance()->setAction(this,_elasticRope,_laughingMan);
    scheduleUpdate();
    
  
    //auto list = obj->getSequences();
    //list["eat"].name
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HelloWorld::loadViewConfig(){
    _visibleSize = Director::getInstance()->getVisibleSize();
    _fanPostion.x = _visibleSize.width*viewConfig::FAN_X;
    _fanPostion.y = _visibleSize.height*viewConfig::FAN_Y;
    
    _laughingManPostion.x = _visibleSize.width*viewConfig::LAUGHINF_MAN_X;
    _laughingManPostion.y = _visibleSize.height*viewConfig::LAUGHINF_MAN_Y;
    
    _elasticRopePostion.x = viewConfig::ELASTIC_ROPE_LEFT_X;
    _elasticRopePostion.y = viewConfig::ELASTIC_ROPE_LEFT_Y;
    
    _washingBirthplacePosition.x =_visibleSize.width*viewConfig::WASHING_BIRTHPLACE_X;
    _washingBirthplacePosition.y = _visibleSize.height*viewConfig::WASHING_BIRTHPLACE_Y;
}
void HelloWorld::initView(){
    //init title
    _title = Sprite::create("title.png");
    float scale = _visibleSize.width/1080.0f;
    _title->setScaleX(scale);
    _title->setScaleY(scale);
    _title->setPosition(_visibleSize.width/2.0f,_visibleSize.height-93.0f/2.0f+20);
    
    //init fan
    _fan = LogoAnimationLoader::loadFengshanNode ();
    _fan->setPosition (_fanPostion);
    _fan->runAction (_fan->getActionTimeline ());
    _fan->getActionTimeline ()->gotoFrameAndPlay (1,true);
    _fan->setScale(0.3f);
    auto fanBg = _fan->getChildByName("background");
    fanBg->setPosition(_fan->getPosition());
    fanBg->setScale(_fan->getScale());
    
    ElasticRope::setVertices(Point(_visibleSize.width*_elasticRopePostion.x,_visibleSize.height*_elasticRopePostion.y)
                             ,Point(_visibleSize.width*(1-_elasticRopePostion.x),_visibleSize.height*_elasticRopePostion.y));
    _elasticRope = ElasticRope::create();
    _elasticRope->setElasticRopeCallback(this);
    _elasticRope->createB2body(_washingBirthplacePosition);
    _laughingMan = LogoActionTimelineNode::create();
    _laughingMan->setPosition(_laughingManPostion);
//    _laughingMan->setGAFPosition(_laughingManPostion);
    //add scene .
    addChild(_fan);
    addChild(_title);
    addChild(_elasticRope);
    addChild(_laughingMan);
  
}
static int scaleAnimation = 0;
static const bool isIOS = CC_TARGET_PLATFORM == 1;
void HelloWorld::onUpdatePosition(Vec2* position)
{
    //同步物理元素与前台元素位置。
    Vec2 vec2 = Vec2(_visibleSize.width/2,position->y);
    if (_washing)
    {
        _washing->setPosition(vec2);
//        if (_washing->getScale() < 1)
//        {
//            _washing->setScale(_washing->getScale()+0.01f);
//        }
    }
    
    switch(LocationAnalyst::doWhat(vec2,1))
    {
        case WASHING_REBIRTH:
            _elasticRope->removeB2body();
            _elasticRope->createB2body(_washingBirthplacePosition);
            LocationAnalyst::state = WASHING_NOTHING;
//            _washing->setScale(0.1f);
            break;
        case WASHING_EAT_FOOD:
            if (LogoActionTimelineNode::currentState != LogoActionTimelineNode::STATE_MOUSE_CLOSE){
                LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_MOUSE_CLOSE;
                _laughingMan->performMouseCloseAnim(false);
               
            }
            
            scaleAnimation = 1;
            break;
        case WASHING_EATED_FOOD:
            LocationAnalyst::state = WASHING_NOTHING;
             _elasticRope->removeB2body();
            _washing->setVisible(false);
            ModelManager::getInstance()->startStandard();
            scaleAnimation = 0;
            if (isIOS){
                viewConfig::working = 1;
            }
            
            break;
    }
}
void HelloWorld::onData(void* data)
{
    auto goodsdata = (GoodsData*)data;
    if (!goodsdata->isCreate())
    {
        
        if (!_washing)
        {
             _washing = Sprite::create(goodsdata->getResPath());
             addChild(_washing);
        }
        else{
            log("change iamge");
            _washing->setTexture(goodsdata->getResPath());
            _washing->setVisible(true);
            _washing->setScale(1.0f);
        }
        _washing->setAnchorPoint(Vec2(0.5f,1.618f));
        goodsdata->setCreate(true);
       
    }
    if (scaleAnimation == 1)
    {
        //放小动画
        if (_washing->getScale() > 0.1)
        _washing->setScale(_washing->getScale()-0.03);
    }
}
void HelloWorld::update(float delta)
{
    static int animation = 0;
    static int limt = CCRANDOM_0_1()*2000;
    if (limt < 500)
    {
        limt = 2000 - limt;
    }
    animation++;
    if (animation % limt+1 == limt)
    {
        limt = CCRANDOM_0_1()*2000;
        if (limt < 500)
        {
            limt = 2000 - limt;
        }
        log("animation");
        if (LogoActionTimelineNode::currentState == LogoActionTimelineNode::STATE_NORMAL)
        _laughingMan->performTongueAnim(false);
    }
    
   
    static int finish = 1;
    if (viewConfig::working == 1)
    {
        viewConfig::working = 2;
        _laughingMan->performWorkingAnim(true);
        finish = 2;
    }
    if (finish>1)
    {
        finish++;
        if (finish > 500)
        {
            if (isIOS)
            {
            LogoActionTimelineNode::currentState = LogoActionTimelineNode::STATE_NORMAL;
            _laughingMan->performTongueAnim(false);
            auto visibleSize = Director::getInstance()->getVisibleSize();
            auto a = (ElasticRopeBox2d::ElasticRope*)(_elasticRope);
            
            a->createB2body(Vec2(visibleSize.width/2,visibleSize.height*viewConfig::LAUGHINF_MAN_Y),1);
            finish = 0;
            }
        }
    }
    
}
