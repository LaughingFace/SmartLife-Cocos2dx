#include "RopeJoin.h"
#include "MouseJoint.h"
#include "../GoodsData.h"
#include "../BodyData.h"
USING_NS_CC;
void RopeJoin::create(b2World* _world,Vec2* leftPoint,Vec2* rightPoint){
    _height = 1000.0f;
         
    auto pointA = Box2DHelper::createCircle(_world,leftPoint->x,leftPoint->y,50,true);
    auto pointB = Box2DHelper::createCircle(_world,rightPoint->x,rightPoint->y,50,true);
/*
    b2RopeJointDef rpa;
    rpa.bodyA = pointA;
    rpa.bodyB = circle;
    rpa.maxLength = 500/32.0f;
    rpa.localAnchorA = b2Vec2_zero;
    rpa.localAnchorB = b2Vec2_zero;

    b2RopeJointDef rpb;
    rpb.bodyA = pointB;
    rpb.bodyB = circle;
    rpb.maxLength = 500/32.0f;
    rpb.localAnchorA = b2Vec2_zero;
    rpb.localAnchorB = b2Vec2_zero;*/




    const float count =(rightPoint->x-leftPoint->x)/100.0f;
    //2、创建刚体所需的形状
    b2CircleShape shapeCircle;
    shapeCircle.m_radius=10.0f/PTM_RATIO;

    //3、声明b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape=&shapeCircle;
        log("i count : %f",count);
    //fixtureDef.friction = 10.0f;
    for (float i = 1; i < count;i++)
    {

        b2BodyDef pabody;
        pabody.type = b2_dynamicBody;
//        log("left i: %f",leftPoint->x+50*i);
//        log("right:i :%f",rightPoint->x-50*i);
        b2BodyDef pbbody;
        pbbody.type = b2_dynamicBody;
        pabody.position.Set((leftPoint->x+50*i)/32.0f,leftPoint->y/32.0f);
        pbbody.position.Set((rightPoint->x-50*i)/32.0f,rightPoint->y/32.0f);
        auto pb = _world->CreateBody(&pbbody);
         pb->CreateFixture(&fixtureDef);
         auto pa = _world->CreateBody(&pabody);
         pa->CreateFixture(&fixtureDef);
        /*
        b2DistanceJointDef dja;
        dja.Initialize(pointA,pa,pointA->GetPosition(),pa->GetPosition());
        dja.collideConnected = true;
        dja.frequencyHz = 20.0f;
       // dja.dampingRatio = 0.1f;
        b2DistanceJointDef djb;
        djb.Initialize(pointB,pb,pointB->GetPosition(),pb->GetPosition());
        djb.collideConnected = true;
        djb.frequencyHz = 20.0f;
        //djb.dampingRatio = 0.1f;
        _world->CreateJoint(&dja);
        _world->CreateJoint(&djb);*/
        if (i == 0)
        {
            b2DistanceJointDef dja;
            dja.Initialize(pointA,pa,pointA->GetPosition(),pa->GetPosition());
            dja.collideConnected = true;
            dja.frequencyHz = 25.0f;
            dja.dampingRatio = 0.5f;
            b2DistanceJointDef djb;
            djb.Initialize(pointB,pb,pointB->GetPosition(),pb->GetPosition());
            djb.collideConnected = true;
            djb.frequencyHz = 25.0f;
            djb.dampingRatio = 0.5f;
            _world->CreateJoint(&dja);
            _world->CreateJoint(&djb);
        }else{

            b2RopeJointDef rpa;
            rpa.bodyA = pointA;
            rpa.bodyB = pa;
            rpa.maxLength = 40/32.0f;
            rpa.localAnchorA =b2Vec2_zero;
            rpa.localAnchorB = b2Vec2_zero;

            b2RopeJointDef rpb;
            rpb.bodyA = pointB;
            rpb.bodyB = pb;
            rpb.maxLength = 40/32.0f;
            rpb.localAnchorA = b2Vec2_zero;
            rpb.localAnchorB = b2Vec2_zero;

            _world->CreateJoint(&rpa);
            _world->CreateJoint(&rpb);
        }

        pointA = pa;
        pointB = pb;


    }

    b2RopeJointDef rpc;
    rpc.bodyA = pointA;
    rpc.bodyB = pointB;
    rpc.maxLength = 50/32.0f;
    rpc.localAnchorA = b2Vec2_zero;
    rpc.localAnchorB = b2Vec2_zero;
    BodyData* data = new BodyData();
    data->data_id = BodyData::BODY_PEAK;
    pointA->SetUserData(data);
    _world->CreateJoint(&rpc);
}

