//
//  LogoAnimFactory.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-24.
//
//

#include "AnimFactory.h"
LogoAnim* AnimFactory::createLogoAnim(AnimImplementType type)
{
    if (type == animTypeGAF)
    {
        return LogoAnimGafImpl::create();
    }
    return nullptr;
}
WarmSwitchAnim* AnimFactory::createWarmSwitchAnim(AnimImplementType type)
{
    if (type == animTypeGAF)
    {
        return nullptr;
    }
    else if (type == animTypeCsb)
    {
        return WarmSwitchCsbImpl::create();
    }
    return nullptr;
}