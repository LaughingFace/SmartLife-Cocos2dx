//
//  WarmSwitchAnimCsbImpl.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-25.
//
//

#include "WarmSwitchAnimCsbImpl.h"
void WarmSwitchCsbImpl::open()
{
//    log("open");
    _atn->getActionTimeline()->gotoFrameAndPlay(0);
    setOpen(true);
}

void WarmSwitchCsbImpl::close(){
//    log("close");
    _atn->getActionTimeline()->gotoFrameAndPause(0);
    setOpen(false);
    
}
Rect WarmSwitchCsbImpl::getBoundingBox() const{
    return _nodeBg->getBoundingBox();
}
bool WarmSwitchCsbImpl::init(){
    WarmSwitchAnim::init();
    auto node = CSLoader::createNode ("fengshan.csb");
    auto timeline = CSLoader::createTimeline ("fengshan.csb");
    
    auto atn = cocostudio::timeline::ActionTimelineNode::create (node,timeline);
    
    auto nodeBg = Sprite::create("fengsan.png");
    nodeBg->setVisible(false);
    nodeBg->setName("background");
    _nodeBg = nodeBg;
    atn->addChild(nodeBg);
    _atn = atn;
    this->addChild(_atn);
    _atn->runAction (_atn->getActionTimeline ());

    if (this->isOpen())
    {
        open();
    }
    else{
        close();
    }
    _atn->setScale(0.3f);
    return true;
}
void WarmSwitchCsbImpl::setPosition(const cocos2d::Vec2 &position){
    WarmSwitchAnim::setPosition(position);
    _nodeBg->setPosition(position);
}