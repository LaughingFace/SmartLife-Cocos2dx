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
#include "cocos2d.h"
USING_NS_CC;
/**
 *笑脸动画，提供笑脸的基本动画，如张嘴，闭嘴等
 */
class LogoAnim :public Node{
public:
    virtual void performWorkingAnim(bool loop) const =0;
    virtual void performTongueAnim(bool loop) const =0;
    virtual void performMouseOpenAnim(bool loop ) const =0;
    virtual void performMouseCloseAnim(bool loop) const =0;
    virtual void performNormalAnim(bool loop ) const =0;
};
#endif /* defined(__cocosProject__LogoAnim__) */



