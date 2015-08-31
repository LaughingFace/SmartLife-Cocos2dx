//
//  LocationAnalyst.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-10.
//
//

#include "LocationAnalyst.h"
#include "HelloworldSceneViewConfig.h"
bool LocationAnalyst::isTouch = true;
int LocationAnalyst::animState = WASHING_NOTHING;
WashingState LocationAnalyst::currentState = state_normal;
const int LocationAnalyst::STATE_FOOD = 10;
const int LocationAnalyst::STATE_REBIRTH = 11;

int LocationAnalyst::underTouchDoWhat(Vec2 location)
{
    static auto _visibleSize = Director::getInstance()->getVisibleSize();

    if (location.y <= _visibleSize.height*viewConfig::ELASTIC_ROPE_LEFT_Y){
        if (location.y <= _visibleSize.height*viewConfig::WASHING_SWAP_LIMIT_Y)
        {
            return WASHING_START;
        }
        else{
            return WASHING_CHANGE;
        }
    }
    else{
        return WASHING_NOTHING;
    }
}
int LocationAnalyst::underStateDoWhat(cocos2d::Vec2 location)
{
    static auto _visibleSize = Director::getInstance()->getVisibleSize();

    if (currentState == state_change)
    {
        if (location.y > _visibleSize.height*(viewConfig::WASHING_BIRTHPLACE_Y))
        {
            //我不要超过出生地，我需要重生。
            log("i am rebirth");
            currentState = state_normal;
            return WASHING_REBIRTH;
        }

    }
    else if (currentState == state_start)
    {
        if (location.y  > _visibleSize.height*(viewConfig::LAUGHINF_MAN_Y + 0.05f))
        {
            currentState = state_normal;
            return WASHING_EATED_FOOD;
        }
        if (location.y  > _visibleSize.height*(viewConfig::LAUGHINF_MAN_Y - 0.07))
        {
            //咦，，，，怎么还没有来吃我，我是食物。
            log("i am food!");
            return WASHING_EAT_FOOD;
        }

    }
    return WASHING_NOTHING;
}
void LocationAnalyst::enterState(WashingState state)
{
    currentState = state;
}
