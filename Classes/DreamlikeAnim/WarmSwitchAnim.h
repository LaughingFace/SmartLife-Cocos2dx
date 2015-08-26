//
//  WarmSwitchAnim.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-25.
//
//

#ifndef __cocosProject__WarmSwitchAnim__
#define __cocosProject__WarmSwitchAnim__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
/**
 *加热开关动画，
 */
class WarmSwitchAnim:public Node{
protected:
    bool _isOpen = false;
    virtual void open()  =0;
    virtual void close()  =0;
public:
    void setOpen(bool b) ;
    bool isOpen();
    virtual bool init();
};
#endif /* defined(__cocosProject__WarmSwitchAnim__) */
