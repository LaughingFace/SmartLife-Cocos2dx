//
//  LogoAnimFactory.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-24.
//
//

#ifndef __cocosProject__LogoAnimFactory__
#define __cocosProject__LogoAnimFactory__

#include <stdio.h>
#include "LogoAnimImpl/LogoAnimGafImpl.h"
#include "WarmSwitchAnimImpl/WarmSwitchAnimCsbImpl.h"
enum AnimImplementType{
    animTypeGAF,animTypeCsb
};
/**
 *Anim动画产品的工厂生成类。
 *创建若干抽象动画产品的实现
 *一个抽象类便是一个产品，一个产品有多种实现。但产品功能不变。
 */
class AnimFactory{
public:
    static LogoAnim* createLogoAnim(AnimImplementType type);
    static WarmSwitchAnim* createWarmSwitchAnim(AnimImplementType type);
};

#endif /* defined(__cocosProject__LogoAnimFactory__) */
