//
//  CurveRope.h
//  cocosProject
//
//  Created by mathcoder23 on 15-8-7.
//
//

#ifndef __cocosProject__CurveRope__
#define __cocosProject__CurveRope__

#include <stdio.h>
#include "cocos2d.h"
#endif /* defined(__cocosProject__CurveRope__) */
USING_NS_CC;
class CurveRope : public Node
{
private:
    Vec2 _leftPoint;
    Vec2 _rightPoint;
    Vec2 _peak;//顶点
    Vec2 _controlLeftPoint;
    Vec2 _controlRightPoint;
    int _curvature = 100;
    
public:
    void setFixationPoint(Vec2& leftPoint,Vec2& rightPoint);
    void setPeak(const Vec2& peak);
    void setCurvature(int curvature);
    Vec2 getLeftPoint();
    virtual bool init();
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    CREATE_FUNC(CurveRope);
};