#include "MouseJoint.h"
#include "RopeJoin.h"
#include "../GoodsData.h"
void MouseJoint::create(b2World* world,Vec2* leftPoint,Vec2* rightPoint){
    _joint = nullptr;
    
    auto body = world->GetBodyList();
    create(world,body);
    
    //rope joint
    RopeJoin rope;
    rope.create(world,leftPoint,rightPoint);
}

void MouseJoint::create(b2World *world, b2Body *body){
    _body = body;
    _world = world;
}
void MouseJoint::move(const cocos2d::Vec2& movePosition)
{
    if (!_body)
    {
        return;
    }
    _isAllowMove = true;
    if (!_joint){
        auto ground = Box2DHelper::createBox(_world,0,0,0.01,0.01,true);
        b2MouseJointDef mouseJoint;
        mouseJoint.bodyA = ground;
        mouseJoint.bodyB = _body;
        
        mouseJoint.target.Set(movePosition.x/PTM_RATIO,movePosition.y/PTM_RATIO);
        mouseJoint.maxForce = 10000000;
        
        _joint = (b2MouseJoint*)_world->CreateJoint(&mouseJoint);
    }
    else{
        b2Vec2 vec2 = b2Vec2(movePosition.x/PTM_RATIO,movePosition.y/PTM_RATIO);
        _joint->SetTarget(vec2);
    }
    
}
void MouseJoint::endMove(){
    if (_joint)
    {
        _world->DestroyJoint(_joint);  
    }

    _joint = nullptr;
    _isAllowMove = false;

}
void MouseJoint::setBody(b2Body *body)
{
    _body = body;
}
bool MouseJoint::isAllowMove(){
    return _isAllowMove;
}
