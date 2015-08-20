//
//  Box2DHelper.cpp
//  Box2DFirst
//
//  Created by JasonWu on 1/8/15.
//
//

#include "Box2DHelper.h"

b2World* Box2DHelper::createWorld()
{
    auto world=new b2World(b2Vec2(0,-50));
    
    return world;
}

b2Body* Box2DHelper::createBox(b2World* world,float posX,float posY,float width,float height,bool isStatic,void* userData)
{
    //1、声明b2BodyDef
    b2BodyDef bodyDef;
    bodyDef.type=isStatic?b2BodyType::b2_staticBody:b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(posX/PTM_RATIO, posY/PTM_RATIO);
    bodyDef.userData=userData;
    
    //2、创建刚体所需的形状
    //   SetAsBox所传入的参数为正方形中心点的右边距和上边距，所以要除以2
    b2PolygonShape shapeBox;
    shapeBox.SetAsBox(width/PTM_RATIO/2, height/PTM_RATIO/2);
    
    //3、声明b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.density=3;//密度
    fixtureDef.friction=0.3;//摩擦系数
    fixtureDef.restitution=0.2;//恢复系数
    fixtureDef.shape=&shapeBox;
    
    //4、创建刚体
    auto box=world->CreateBody(&bodyDef);
    box->CreateFixture(&fixtureDef);
    
    return box;
}

b2Body* Box2DHelper::createCircle(b2World* world,float posX,float posY, float radius, bool isStatic, void* userData){
    //1、声明b2BodyDef
    b2BodyDef bodyDef;
    bodyDef.type=isStatic?b2BodyType::b2_staticBody:b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(posX/PTM_RATIO, posY/PTM_RATIO);
    bodyDef.userData=userData;
    bodyDef.angularDamping=20.0f;//刚体角速度阻尼。
    bodyDef.linearDamping=0.1f;//刚体线速度阻尼。
    //2、创建刚体所需的形状
    b2CircleShape shapeCircle;
    shapeCircle.m_radius=radius/PTM_RATIO;
    
    //3、声明b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.density=0.30;
    fixtureDef.friction=1000;
    fixtureDef.restitution=0.01;
    fixtureDef.shape=&shapeCircle;
    
    //4、创建刚体
    auto circle=world->CreateBody(&bodyDef);
    circle->CreateFixture(&fixtureDef);

    return circle;
}


void Box2DHelper::createWrapWall(b2World* world,float width,float height,void* userData)
{
    
    float wallThick = 20;//墙壁厚度
    
    createBox(world, width / 2, 0, width , wallThick, true,userData);
    createBox(world, width / 2, height, width , wallThick, true,userData);
    createBox(world, 0, height / 2, wallThick, height , true,userData);
    createBox(world, width, height / 2, wallThick, height , true,userData);
    
    
}
b2Body* Box2DHelper::createEdge(b2World* world,float posX,float posY,float posAX,float posAY,float posBX,float posBY,bool isStatic, void* userData)
{
    //1、声明b2BodyDef
    b2BodyDef bodyDef;
    bodyDef.type=isStatic?b2BodyType::b2_staticBody:b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(posX/PTM_RATIO, posY/PTM_RATIO);
    bodyDef.userData=userData;
    
    //2、创建刚体所需的形状
    b2EdgeShape shapeEdge;
    shapeEdge.Set(b2Vec2(posAX/PTM_RATIO,posAY/PTM_RATIO), b2Vec2(posBX/PTM_RATIO,posBY/PTM_RATIO));
    
    //3、声明b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.density=3;//密度
    fixtureDef.friction=0.3;//摩擦系数
    fixtureDef.restitution=0.2;//恢复系数
    fixtureDef.shape=&shapeEdge;
    
    //4、创建刚体
    auto edge=world->CreateBody(&bodyDef);
    edge->CreateFixture(&fixtureDef);
    
    return edge;
}

b2Body* Box2DHelper::createChain(b2World* world,float posX,float posY,b2Vec2* vertices,int count,bool isStatic, void* userData)
{
    //1、声明b2BodyDef
    b2BodyDef bodyDef;
    bodyDef.type=isStatic?b2BodyType::b2_staticBody:b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(posX/PTM_RATIO, posY/PTM_RATIO);
    bodyDef.userData=userData;
    
    //2、创建刚体所需的形状
    for (int i=0; i<count; i++) {
        vertices[i]*=1/PTM_RATIO;
    }
    b2ChainShape shapeShape;
    shapeShape.CreateChain(vertices, count);
    
    //3、声明b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.density=3;//密度
    fixtureDef.friction=0.3;//摩擦系数
    fixtureDef.restitution=0.2;//恢复系数
    fixtureDef.shape=&shapeShape;
    
    //4、创建刚体
    auto edge=world->CreateBody(&bodyDef);
    edge->CreateFixture(&fixtureDef);
    
    return edge;
}
