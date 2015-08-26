//
//  LogoAnimGafImpl.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-24.
//
//

#include "LogoAnimGafImpl.h"
using namespace std;
string gafPath = "LogoFaceAnim/LogoFaceAnim.gaf";
string animNormal = "normal";
string animWorking = "working";
string animOpemMouse = "openmouse";
string animCloseMouse = "closemouse";
string animEat = "eat";

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
void LogoAnimGafImpl::performWorkingAnim(bool loop) {
    _gafAnim->playSequence(animWorking,loop);
}
void LogoAnimGafImpl::performTongueAnim(bool loop) {
    _gafAnim->playSequence(animEat, loop);
    finishedNormalAnim();
}
void LogoAnimGafImpl::performMouseOpenAnim(bool loop) {
    _gafAnim->playSequence(animOpemMouse, loop);
}
void LogoAnimGafImpl::performMouseCloseAnim(bool loop) {
    _gafAnim->playSequence(animCloseMouse, loop);
    finishedNormalAnim();
}
void LogoAnimGafImpl::performNormalAnim(bool loop) {
    _gafAnim->playSequence(animNormal, loop);
}
Rect LogoAnimGafImpl::getBoundingBox() const{
    return _gafAnim->getBoundingBox();
}
void LogoAnimGafImpl::finishedNormalAnim(){
    _gafAnim->setAnimationFinishedPlayDelegate([this](GAFObject* gafObject){
        this->performNormalAnim();
        this->_gafAnim->setAnimationFinishedPlayDelegate(nullptr);
    });
}