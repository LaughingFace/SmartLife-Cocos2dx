#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Box2DHelper.h"
USING_NS_CC;
class RopeJoin
{
private:
        float _height;
        b2MouseJoint* _joint;
        b2Body* _body;
public:
    void create(b2World* world,Vec2* leftPoint,Vec2* rightPoint);
};
