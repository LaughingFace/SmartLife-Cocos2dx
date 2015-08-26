
//
//  LocationAnalyst.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-10.
//
//

#ifndef __cocosProject__LocationAnalyst__
#define __cocosProject__LocationAnalyst__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#endif /* defined(__cocosProject__LocationAnalyst__) */
#define WASHING_CHANGE 1//切换洗涤物。
#define WASHING_SELECT 2//选择洗涤物。
#define WASHING_NOTHING 3//你似乎没什么可以干。
#define WASHING_REBIRTH 4//重生。
#define WASHING_EAT_FOOD 5//吃食物啦。
#define WASHING_EATED_FOOD 6//吃完了。

class LocationAnalyst{
public:
    static bool isTouch;
    static const int STATE_REBIRTH ;//我要重生
    static const int STATE_FOOD ;//我是食物
    static int state;//洗涤物状态
    static int doWhat(Vec2 location,int who);//我在哪里，我需要做什么。
};