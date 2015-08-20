#include "logoanimationloader.h"

ActionTimelineNode* LogoAnimationLoader::loadMouseNode ()
{
    //LogoAnimationLoader::load ("logo_mouse_open.csb");

    auto node = CSLoader::createNode ("logo_mouse_open.csb");
     auto timeline = CSLoader::createTimeline ("logo_mouse_open.csb");
    auto atn = ActionTimelineNode::create (node,timeline);
    atn->getBoundingBox().size = node->getBoundingBox().size;
    return atn;
}
ActionTimelineNode* LogoAnimationLoader::loadMouseCloseNode()
{
    auto node = CSLoader::createNode ("logo_mouse_close.csb");
     auto timeline = CSLoader::createTimeline ("logo_mouse_close.csb");
    auto atn = ActionTimelineNode::create (node,timeline);

    return atn;
}//

ActionTimelineNode* LogoAnimationLoader::loadFengshanNode ()
{
    //LogoAnimationLoader::load ("logo_mouse.csb");

    auto node = CSLoader::createNode ("fengshan.csb");
     auto timeline = CSLoader::createTimeline ("fengshan.csb");
    
    auto atn = ActionTimelineNode::create (node,timeline);
    
    auto nodeBg = Sprite::create("fengsan.png");
    nodeBg->setVisible(false);
    nodeBg->setName("background");
    atn->addChild(nodeBg);
    return atn;

}
 ActionTimelineNode* LogoAnimationLoader::loadWorkingNode()
{
    //LogoAnimationLoader::load ("logo_working.csb");
     auto node = CSLoader::createNode ("logo_working.csb");
      auto timeline = CSLoader::createTimeline ("logo_working.csb");
     auto atn = ActionTimelineNode::create (node,timeline);

     return atn;
}

 ActionTimelineNode* LogoAnimationLoader::loadTongueNode()
{
//    LogoAnimationLoader::load ("logo_tuse.csb");
     auto node = CSLoader::createNode ("logo_tuse.csb");
      auto timeline = CSLoader::createTimeline ("logo_tuse.csb");
     auto atn = ActionTimelineNode::create (node,timeline);

     return atn;
}
