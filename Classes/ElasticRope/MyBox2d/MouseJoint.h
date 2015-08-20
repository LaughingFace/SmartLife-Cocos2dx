#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Box2DHelper.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace cocostudio::timeline;
class MouseJoint
{
private:
    b2MouseJoint* _joint;
    b2Body* _body;
    b2World* _world;
    bool _isAllowMove = false;
public:
    void create(b2World* world,Vec2* leftPoint,Vec2* rightPoint);
    void create(b2World* world,b2Body* body);
    void move(const Vec2& movePosition);
    bool isAllowMove();//是否允许移动。
    void endMove();
    void setBody(b2Body* body);
};
