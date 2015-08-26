//
//  Box2DDebugDraw.h
//  Box2DFirst
//
//  Created by JasonWu on 1/8/15.
//
//

#ifndef __Box2DFirst__Box2DDebugDraw__
#define __Box2DFirst__Box2DDebugDraw__

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Box2DDebugDraw:public b2Draw
{
protected:
    float32 _ratio;

    cocos2d::DrawNode* _graphics;

public:
    Box2DDebugDraw(cocos2d::DrawNode* graphics);

    Box2DDebugDraw(cocos2d::DrawNode* graphics,float32 ratio);

    /// Draw a closed polygon provided in CCW order.
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    /// Draw a solid closed polygon provided in CCW order.
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    /// Draw a circle.
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

    /// Draw a solid circle.
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

    /// Draw a line segment.
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

    /// Draw a transform. Choose your own length scale.
    /// @param xf a transform.
    virtual void DrawTransform(const b2Transform& xf);
};

#endif /* defined(__Box2DFirst__Box2DDebugDraw__) */
