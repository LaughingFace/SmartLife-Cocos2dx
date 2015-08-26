#include "ElasticRope.h"
#include "MyBox2d/RopeJoin.h"
#include "ElasticRopeConfig.h"
#include "logoanimationloader.h"
#include "modelmanager.h"

#include "BodyData.h"
namespace ElasticRopeBox2d {
    void ElasticRopeCallback::onUpdatePosition(cocos2d::Vec2 *position){
        
    }
    void ElasticRopeCallback::onData(void *data){
        
    }
    static Vec2 _leftPoint;
     static Vec2 _rightPoint;
     void ElasticRope::setVertices(Vec2 leftPoint, Vec2 rightPoint){
          _leftPoint = leftPoint;
          _rightPoint = rightPoint;
     }
     
     bool ElasticRope::init(){
          initStyle(1);
          //left point draw;
        leftOutCircle = FixationPoint::create();
          leftOutCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
          leftOutCircle->setRadius(_circleOutRadius);
          leftOutCircle->setPosition(_leftPoint.x,_leftPoint.y);
          
        leftBetweenCircle = FixationPoint::create();
          leftBetweenCircle->setColor(_circleBetweenColorR,_circleBetweenColorG,_circleBetweenColorB,_circleBetweenColorA);
          leftBetweenCircle->setRadius(_circleBetweenRadius);
          leftBetweenCircle->setPosition(_leftPoint.x,_leftPoint.y);
          
        leftInCircle = FixationPoint::create();
          leftInCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
          leftInCircle->setRadius(_circleInRadius);
          leftInCircle->setPosition(_leftPoint.x,_leftPoint.y);
          
          
          //right point draw;
        rightOutCircle = FixationPoint::create();
          rightOutCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
          rightOutCircle->setRadius(_circleOutRadius);
          rightOutCircle->setPosition(_rightPoint.x,_rightPoint.y);
          
        rightBetweenCircle = FixationPoint::create();
          rightBetweenCircle->setColor(_circleBetweenColorR,_circleBetweenColorG,_circleBetweenColorB,_circleBetweenColorA);
          rightBetweenCircle->setRadius(_circleBetweenRadius);
          rightBetweenCircle->setPosition(_rightPoint.x,_rightPoint.y);
          
        rightInCircle = FixationPoint::create();
          rightInCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
          rightInCircle->setRadius(_circleInRadius);
          rightInCircle->setPosition(_rightPoint.x,_rightPoint.y);
          //        auto leftRopePoint = Sprite::create("ropepoint1.png");
          //        leftRopePoint->setPosition(_leftPoint.x,_leftPoint.y);
          //        leftRopePoint->setScale(0.1f);
          //        addChild(leftRopePoint);
          //        auto rightRopePoint = Sprite::create("ropepoint1.png");
          //        rightRopePoint->setPosition(_rightPoint.x,_rightPoint.y);
          //        rightRopePoint->setScale(0.1f);
          //        addChild(rightRopePoint);
          
          
          drawRope();
          //show draw
         
          //draw curve rope;
         _curveRope = CurveRope::create();
         _curveRope->setPeak(Vec2(Director::getInstance()->getVisibleSize().width/2,400));
         _curveRope->setFixationPoint(_leftPoint, _rightPoint);
         _curveRope->setCurvature(70);
          addChild(rightOutCircle);
          addChild(leftOutCircle);
           addChild(_curveRope);
         addChild(leftBetweenCircle);
          addChild(leftInCircle);
          
         
          addChild(rightBetweenCircle);
          addChild(rightInCircle);
        
         addChild(_graphics);
        
          scheduleUpdate();
          return true;
     }
    void ElasticRope::drawPoint()
    {
        //left point draw;
        leftOutCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
//        leftOutCircle->setRadius(_circleOutRadius);
//        leftOutCircle->setPosition(_leftPoint.x,_leftPoint.y);
        
//        leftBetweenCircle = FixationPoint::create();
        leftBetweenCircle->setColor(_circleBetweenColorR,_circleBetweenColorG,_circleBetweenColorB,_circleBetweenColorA);
//        leftBetweenCircle->setRadius(_circleBetweenRadius);
//        leftBetweenCircle->setPosition(_leftPoint.x,_leftPoint.y);
        
//        leftInCircle = FixationPoint::create();
        leftInCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
//        leftInCircle->setRadius(_circleInRadius);
//        leftInCircle->setPosition(_leftPoint.x,_leftPoint.y);
        
        
        //right point draw;
//        rightOutCircle = FixationPoint::create();
        rightOutCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
//        rightOutCircle->setRadius(_circleOutRadius);
//        rightOutCircle->setPosition(_rightPoint.x,_rightPoint.y);
        
//        rightBetweenCircle = FixationPoint::create();
        rightBetweenCircle->setColor(_circleBetweenColorR,_circleBetweenColorG,_circleBetweenColorB,_circleBetweenColorA);
//        rightBetweenCircle->setRadius(_circleBetweenRadius);
//        rightBetweenCircle->setPosition(_rightPoint.x,_rightPoint.y);
        
//        rightInCircle = FixationPoint::create();
        rightInCircle->setColor(_circleColorR,_circleColorG,_circleColorB,_circleColorA);
//        rightInCircle->setRadius(_circleInRadius);
//        rightInCircle->setPosition(_rightPoint.x,_rightPoint.y);

    }
    
     void ElasticRope::drawRope()
     {
          cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
          _graphics=DrawNode::create();
          _graphics->setAnchorPoint(Vec2::ZERO);
          
          auto debugdraw=new Box2DDebugDraw(_graphics,PTM_RATIO);
          _world = new b2World(b2Vec2(0,-10));
          _world->SetDebugDraw(debugdraw);
          ModelManager::getInstance()->setWorld(_world);
          uint32 flags = 0;
          flags += b2Draw::e_shapeBit;
          flags += b2Draw::e_jointBit;
          flags += b2Draw::e_aabbBit;
          flags += b2Draw::e_pairBit;
          flags += b2Draw::e_centerOfMassBit;
          debugdraw->SetFlags(flags);
          
          
          
          //Box2DHelper::createCircle(_world,visibleSize.width/2,visibleSize.height/2,20.0f);
          Box2DHelper::createWrapWall(_world, visibleSize.width, visibleSize.height*2);
          //mouse event.
          
          _mouseJoint = new MouseJoint();
          _mouseJoint->create(_world,&_leftPoint,&_rightPoint);
        
     }
    
     void ElasticRope::update(float delta){
          _graphics->clear();//清空绘图
          _world->Step(1.0f/60.0f, 6, 2);//刷新物理世界。
//          _world->DrawDebugData();//绘制调试试图。
          b2Body* body = _world->GetBodyList();
          while (body)
          {
               if ( body->GetUserData())
               {
                   BodyData* data = (BodyData*)body->GetUserData();
                   if(data->data_id == BodyData::BODY_CIRCLE)
                   {
                       if(_callback)
                       {
                           _elasticRopePostion->set(body->GetPosition().x*PTM_RATIO,body->GetPosition().y*PTM_RATIO);
                           _callback->onData(data->data);
                           _callback->onUpdatePosition(_elasticRopePostion);
                       }
                   }
                   else if(data->data_id == BodyData::BODY_PEAK)
                   {
                       auto yy = body->GetPosition().y*PTM_RATIO;
//                       if (_curveRope->getLeftPoint().y -yy < 15)
//                       {
//                           yy = _curveRope->getLeftPoint().y;
//                       }
                       _curveRope->setPeak(Vec2(Director::getInstance()->getVisibleSize().width/2,yy));
                   }
                  
                }
               body = body->GetNext();
          }
          
     }
     void ElasticRope::initStyle(int id){
          if (id == 0)
          {
               _circleColorR = style1::ROPE_POINT_CIRCLE_COLOR_R;
               _circleColorG = style1::ROPE_POINT_CIRCLE_COLOR_G;
               _circleColorB = style1::ROPE_POINT_CIRCLE_COLOR_B;
               _circleColorA = style1::ROPE_POINT_CIRCLE_COLOR_A;
               
               _circleBetweenColorR = style1::ROPE_POINT_CIRCLE_BETWEEN_COLOR_R;
               _circleBetweenColorG = style1::ROPE_POINT_CIRCLE_BETWEEN_COLOR_G;
               _circleBetweenColorB = style1::ROPE_POINT_CIRCLE_BETWEEN_COLOR_B;
               _circleBetweenColorA = style1::ROPE_POINT_CIRCLE_BETWEEN_COLOR_A;
               
               _circleInRadius = style1::ROPE_POINT_IN_RADIUS;
               _circleOutRadius = style1::ROPE_POINT_OUT_RADIUS;
               _circleBetweenRadius = style1::ROPE_POINT_BETWEEN_RADIUS;
          }
          else
          {
               _circleColorR = style2::ROPE_POINT_CIRCLE_COLOR_R;
               _circleColorG = style2::ROPE_POINT_CIRCLE_COLOR_G;
               _circleColorB = style2::ROPE_POINT_CIRCLE_COLOR_B;
               _circleColorA = style2::ROPE_POINT_CIRCLE_COLOR_A;
               
               _circleBetweenColorR = style2::ROPE_POINT_CIRCLE_BETWEEN_COLOR_R;
               _circleBetweenColorG = style2::ROPE_POINT_CIRCLE_BETWEEN_COLOR_G;
               _circleBetweenColorB = style2::ROPE_POINT_CIRCLE_BETWEEN_COLOR_B;
               _circleBetweenColorA = style2::ROPE_POINT_CIRCLE_BETWEEN_COLOR_A;
               
               _circleInRadius = style2::ROPE_POINT_IN_RADIUS;
               _circleOutRadius = style2::ROPE_POINT_OUT_RADIUS;
               _circleBetweenRadius = style2::ROPE_POINT_BETWEEN_RADIUS;
          }
          
     }
    void ElasticRope::setElasticRopeCallback(ElasticRopeBox2d::ElasticRopeCallback *callback)
    {
        _callback = callback;
    }
    MouseJoint* ElasticRope::getMovePermission(){
        return _mouseJoint;
    }
    void ElasticRope::removeB2body(){
        if(_body)
        {
            _world->DestroyBody(_body);
            _body = nullptr;
        }
    }
    b2Body* ElasticRope::createB2body(Vec2 position)
    {
        BodyData* bodyData = new BodyData();
        bodyData->data_id = BodyData::BODY_CIRCLE;
        bodyData->data =GoodsData::getNext();
        auto body =  Box2DHelper::createCircle(_world, position.x, position.y, 100,false,bodyData);
        static auto bodyLime = Box2DHelper::createBox(_world, position.x-120, position.y, 1, 1000,true);
        static auto bodyLimeRight = Box2DHelper::createBox(_world, position.x+120, position.y, 1, 1000,true);
//        auto body = Box2DHelper::createBox(_world, position->x, position->y,300.0f, 300.0f,false,bodyData);
        _mouseJoint->setBody(body);
        _body = body;
        return body;
    }
    b2Body* ElasticRope::createB2body(Vec2 position,int i)
    {
        BodyData* bodyData = new BodyData();
        bodyData->data_id = BodyData::BODY_CIRCLE;
        bodyData->data =GoodsData::getGoodsDataList();
        auto body =  Box2DHelper::createCircle(_world, position.x, position.y, 100,false,bodyData);
        static auto bodyLime = Box2DHelper::createBox(_world, position.x-120, position.y, 1, 1000,true);
        static auto bodyLimeRight = Box2DHelper::createBox(_world, position.x+120, position.y, 1, 1000,true);
        //        auto body = Box2DHelper::createBox(_world, position->x, position->y,300.0f, 300.0f,false,bodyData);
        _mouseJoint->setBody(body);
        _body = body;
        return body;
    }
    void ElasticRope::style1(){
        initStyle(1);
        drawPoint();
    }
    void ElasticRope::style2(){
        initStyle(0);
        drawPoint();
    }
}
