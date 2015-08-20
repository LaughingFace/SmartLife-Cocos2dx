//
//  Box2DDebugDraw.cpp
//  Box2DFirst
//
//  Created by JasonWu on 1/8/15.
//
//

#include "Box2DDebugDraw.h"

USING_NS_CC;

Box2DDebugDraw::Box2DDebugDraw(cocos2d::DrawNode* graphics)
: _ratio( 1.0f ),_graphics(graphics)
{
}

Box2DDebugDraw::Box2DDebugDraw( cocos2d::DrawNode* graphics,float32 ratio)
: _ratio( ratio ),_graphics(graphics)
{
}


void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    //绘制多边形
    Vec2* newVertices=new Vec2[vertexCount];
    for( int i=0;i<vertexCount;i++)
    {
        newVertices[i].set(vertices[i].x, vertices[i].y);
        newVertices[i]*=_ratio;
    }

    _graphics->drawPolygon(newVertices, vertexCount, Color4F(color.r,color.g,color.b,0.25f), 0, Color4F());

    delete[] newVertices;
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    //绘制带描边的多边形
//
    Vec2* newVertices=new Vec2[vertexCount];
    for( int i=0;i<vertexCount;i++)
    {
        newVertices[i].set(vertices[i].x, vertices[i].y);
        newVertices[i]*=_ratio;
    }

    _graphics->drawPolygon(newVertices, vertexCount, Color4F(color.r*0.5f,color.g*0.5f,color.b*0.5f,0.5f), 1, Color4F(color.r,color.g,color.b,1.0f));

    delete [] newVertices;
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    //绘制圆
    Vec2 newCenter;
    newCenter.set(center.x*_ratio, center.y*_ratio);
    _graphics->drawSolidCircle(newCenter, (radius+50)*_ratio, 0, 16, Color4F(color.r*0.0f,color.g*0.0f,color.b,1.0f));
    _graphics->drawSolidCircle(newCenter, radius*_ratio, 0, 16, Color4F(color.r,0.0f,color.b,1.0f));
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

    Vec2 newCenter;
    newCenter.set(center.x*_ratio, center.y*_ratio);

    //绘制圆
    _graphics->drawSolidCircle(newCenter, radius*_ratio, 0, 16, Color4F(color.r*0.0f,color.g*0.5f,color.b*0.5f,0.5f));

   // 绘制边
    _graphics->drawCircle(newCenter, radius*_ratio, 0, 16, false, Color4F(color.r,color.g,color.b,1.0f));


}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    //绘制线段
    Vec2 newP1,newP2;
    newP1.set(p1.x*_ratio, p1.y*_ratio);
    newP2.set(p2.x*_ratio, p2.y*_ratio);

    _graphics->drawSegment(newP1,newP2,1.5f,Color4F(31.0f/255.0f,26.0f/255.0f,23.0f/255.0f,1.0f));
}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{
    //绘制坐标轴变换
    Vec2 p1, p2;
    p1.set(xf.p.x, xf.p.y);
    const float32 scale = 0.4f;//轴的长度缩放

    p2.set(xf.q.GetXAxis().x, xf.q.GetXAxis().y);
    p2 = p1 + scale * p2;
    _graphics->drawSegment(p1*_ratio,p2*_ratio,1,Color4F(1.0f,0,0,1.0f));

    p2.set(xf.q.GetYAxis().x, xf.q.GetYAxis().y);
    p2 = p1 + scale * p2;
    _graphics->drawSegment(p1*_ratio,p2*_ratio,1,Color4F(0,1.0f,0,1.0f));
}
