//
//  LogoAnimGafImpl.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-24.
//
//

#include "LogoAnimGafImpl.h"
std::string gafPath = "LogoFaceAnim/LogoFaceAnim.gaf";
std::string animNormal = "normal";
std::string animWorking = "eating";
bool LogoAnimGafImpl::init()
{
    auto gafAsset = gaf::GAFAsset::create(gafPath);
    _gafAnim = gafAsset->createObject();
    _gafAnim->setAnchorPoint(Vec2(0.5f,0.5f));//设置gaf动画锚点为中心。
    _gafAnim->start();
    this->addChild(_gafAnim);
    performNormalAnim();
    return true;
}
void LogoAnimGafImpl::performWorkingAnim(bool loop) const{
    
}
void LogoAnimGafImpl::performTongueAnim(bool loop) const{
    
}
void LogoAnimGafImpl::performMouseOpenAnim(bool loop) const{
    
}
void LogoAnimGafImpl::performMouseCloseAnim(bool loop) const{
    
}
void LogoAnimGafImpl::performNormalAnim(bool loop) const{
    _gafAnim->playSequence(animNormal, loop);
}
Rect LogoAnimGafImpl::getBoundingBox() const{
    return _gafAnim->getBoundingBox();
}