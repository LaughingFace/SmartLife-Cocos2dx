//
//  WarmSwitchAnimCsbImpl.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-25.
//
//

#ifndef __cocosProject__WarmSwitchAnimCsbImpl__
#define __cocosProject__WarmSwitchAnimCsbImpl__

#include <stdio.h>
#include "../WarmSwitchAnim.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
class WarmSwitchCsbImpl :public WarmSwitchAnim{
private:
    Sprite* _nodeBg;
    cocostudio::timeline::ActionTimelineNode* _atn;
protected:
    virtual void open() ;
    virtual void close() ;
public:
    virtual bool init();
    virtual void setPosition(const Vec2& position);
    CREATE_FUNC(WarmSwitchCsbImpl);
    virtual Rect getBoundingBox() const;
};
#endif /* defined(__cocosProject__WarmSwitchAnimCsbImpl__) */
