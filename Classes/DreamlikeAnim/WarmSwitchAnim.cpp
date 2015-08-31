//
//  WarmSwitchAnim.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-25.
//
//

#include "WarmSwitchAnim.h"
bool WarmSwitchAnim::init()
{
    auto NodeListener = EventListenerTouchOneByOne::create();
    NodeListener->onTouchBegan = [this](Touch* touch,Event* event){
//        log("size::::::::%f",this->getBoundingBox().size.width);
        if(this->getBoundingBox().containsPoint(touch->getLocation()))
        {
            if (this->isOpen())
            {
//                log("base isopen = true");
                this->close();
            }
            else{
                this->open();
//                log("base isopen = false");

            }
            return true;
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority (NodeListener,this);
    return true;
}
bool WarmSwitchAnim::isOpen(){
    return _isOpen;
}
void WarmSwitchAnim::setOpen(bool b)
{
    _isOpen = b;
}