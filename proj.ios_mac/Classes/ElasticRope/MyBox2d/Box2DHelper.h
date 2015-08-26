//
//  Box2DHelper.h
//  Box2DFirst
//
//  Created by JasonWu on 1/8/15.
//
//

#ifndef __Box2DFirst__Box2DHelper__
#define __Box2DFirst__Box2DHelper__

#include <stdio.h>
#include "Box2D/Box2D.h"


#define PTM_RATIO 32.0f

class Box2DHelper
{

public:

    //创建物理世界
    static b2World* createWorld();
    
    //创建方形
    static b2Body* createBox(b2World* world,float posX,float posY,float width,float height,bool isStatic = false,void* userData=nullptr);
    
    //创建圆形
    static b2Body* createCircle(b2World* world,float posX,float posY, float radius, bool isStatic = false, void* userData=nullptr);
    
    //创建围墙
    static void createWrapWall(b2World* world,float width,float height,void* userData=nullptr);
    
    //创建边缘
    static b2Body* createEdge(b2World* world,float posX,float posY,float posAX,float posAY,float posBX,float posBY,bool isStatic = false, void* userData=nullptr);

    //创建链形
    static b2Body* createChain(b2World* world,float posX,float posY,b2Vec2* vertices,int count,bool isStatic = false, void* userData=nullptr);

};

#endif /* defined(__Box2DFirst__Box2DHelper__) */
