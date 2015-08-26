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
int LocationAnalyst::state = WASHING_NOTHING;
const int LocationAnalyst::STATE_FOOD = 10;
const int LocationAnalyst::STATE_REBIRTH = 11;
int LocationAnalyst::doWhat(Vec2 location,int who){
    if (who == 1 && isTouch)
    {
        return WASHING_NOTHING;
    }
    static auto _visibleSize = Director::getInstance()->getVisibleSize();
    auto yy = location.y;
    if (yy <= _visibleSize.height*viewConfig::ELASTIC_ROPE_LEFT_Y)
    {
        if (state == WASHING_NOTHING)
        {
            if (yy >= _visibleSize.height*viewConfig::WASHING_SWAP_LIMIT_Y){
                //切换模式
                log("change");
                return WASHING_CHANGE;
            }
            else{
                //选择模式
                log("select");
                return WASHING_SELECT;
            }
        }
        
    }
    else {
        if (state == STATE_REBIRTH && yy > _visibleSize.height*(viewConfig::WASHING_BIRTHPLACE_Y))
        {
            //我不要超过出生地，我需要重生。
             log("i am rebirth");
            return WASHING_REBIRTH;
        }
        if (state == STATE_FOOD && yy > _visibleSize.height*(viewConfig::LAUGHINF_MAN_Y + 0.05f))
        {
            
            return WASHING_EATED_FOOD;
        }
        if (state == STATE_FOOD && yy > _visibleSize.height*(viewConfig::LAUGHINF_MAN_Y - 0.07))
        {
            //咦，，，，怎么还没有来吃我，我是食物。
             log("i am food!");
            return WASHING_EAT_FOOD;
        }
        
    }
//    log("nothing");
    return WASHING_NOTHING;
}