//
//  LogoAnim.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-24.
//
//

#ifndef __cocosProject__LogoAnim__
#define __cocosProject__LogoAnim__

#include <stdio.h>

#endif /* defined(__cocosProject__LogoAnim__) */

#include "cocos2d.h"
USING_NS_CC;
class LogoAnim : public Node{
public:
    virtual void performWorkingAnim(bool loop = false);
    virtual void performTongueAnim(bool loop = false);
    virtual void performMouseOpenAnim(bool loop = false);
    virtual void performMouseCloseAnim(bool loop = false);
    virtual void performNormalAnim(bool loop = false);
};
