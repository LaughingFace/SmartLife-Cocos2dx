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

#endif /* defined(__cocosProject__LogoAnimFactory__) */
#include "LogoAnim.h"
class LogoAnimFactory{
public:
    static const int GAF_ANIM;
    static LogoAnim* buildLogoAnim(int i);
};