//
//  CurveRope.cpp
//  cocosProject
//
//  Created by mathcoder23 on 15-8-7.
//
//

#include "CurveRope.h"
bool CurveRope::init()
{
    return true;
}
void CurveRope::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
    glLineWidth(4);
    DrawPrimitives::setDrawColor4B(0, 0, 0, 255);//颜色
    //粗细
    _controlLeftPoint.x = _peak.x - _curvature;
    _controlRightPoint.x = _peak.x + _curvature;
    
    _controlLeftPoint.y = _peak.y;
    _controlRightPoint.y = _peak.y;
    DrawPrimitives::drawCubicBezier(_leftPoint, _controlLeftPoint, _peak, _peak, 200);
    DrawPrimitives::drawCubicBezier(_rightPoint,  _controlRightPoint,_peak, _peak, 200);
}
void CurveRope::setFixationPoint(Vec2& leftPoint,Vec2& rightPoint)
{
    _leftPoint = leftPoint;
    _rightPoint = rightPoint;
}
void CurveRope::setPeak(const Vec2& peak)
{
    _peak = peak;
}
void CurveRope::setCurvature(int curvature)
{
    _curvature = curvature;
}
Vec2 CurveRope::getLeftPoint(){
    return _leftPoint;
}