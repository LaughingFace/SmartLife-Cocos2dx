#ifndef LOGOANIMATIONLOADER_H
#define LOGOANIMATIONLOADER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoStudio.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;


class LogoAnimationLoader
{
private:
        LogoAnimationLoader(){}


public:
       static ActionTimelineNode* loadMouseNode();
       static ActionTimelineNode* loadWorkingNode();
       static ActionTimelineNode* loadTongueNode();
       static ActionTimelineNode* loadFengshanNode();
       static ActionTimelineNode* loadMouseCloseNode();

//       static ActionTimelineNode* load(const std::string& filename)
//    {
//          auto node = CSLoader::createNode (filename);
//           auto timeline = CSLoader::createTimeline (filename);
//          auto atn = ActionTimelineNode::create (node,timeline);

//          return atn;
//      }


};

#endif // LOGOANIMATIONLOADER_H
