#include "cocos2d.h"
#include "FixationPoint.h"
#include "MyBox2d/Box2DDebugDraw.h"
#include "MyBox2d/Box2DHelper.h"
#include "Box2D/Box2D.h"
#include "MyBox2d/MouseJoint.h"
#include "cocostudio/CocoStudio.h"
#include "CurveRope.h"
#include "GoodsData.h"
USING_NS_CC;
using namespace cocostudio::timeline;
namespace ElasticRopeBox2d {
    class ElasticRopeCallback{
    public:
        virtual void onUpdatePosition(Vec2* position);
        virtual void onData(void* data);
    };
    class ElasticRope : public Node{
    private:
        FixationPoint* leftOutCircle;
        FixationPoint* leftBetweenCircle;
        FixationPoint* leftInCircle;
        
        FixationPoint* rightOutCircle;
        FixationPoint* rightBetweenCircle;
        FixationPoint* rightInCircle;
        
        DrawNode* _graphics;
        b2World* _world;
        MouseJoint* _mouseJoint;
        Sprite* _sprite;
        b2Body* _body;
        CurveRope* _curveRope;
        int _circleColorR;
        int _circleColorG;
        int _circleColorB;
        int _circleColorA;
        
        int _circleBetweenColorR;
        int _circleBetweenColorG;
        int _circleBetweenColorB;
        int _circleBetweenColorA;
        
        float _circleOutRadius;
        float _circleInRadius;
        float _circleBetweenRadius;
        ElasticRopeCallback* _callback;
        Vec2* _elasticRopePostion = new Vec2();
        void drawRope();
        void initStyle(int id);
        void drawPoint();
    public:
        static void setVertices(Vec2 leftPoint,Vec2 rightPoint);
        void setElasticRopeCallback(ElasticRopeCallback* callback);
        MouseJoint* getMovePermission();
        virtual void update(float delta);
        virtual bool init();
        b2Body* createB2body(Vec2 position);
        b2Body* createB2body(Vec2 position,int i);
        void removeB2body();
        void style1();
        void style2();
        CREATE_FUNC(ElasticRope) ;
    };
}
