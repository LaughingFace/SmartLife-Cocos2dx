#include "mysprite.h"

MySprite::MySprite()
{

}

void MySprite::prepare ()
{

    this->setAnchorPoint (Vect(0.5,1));
            auto listener = EventListenerTouchOneByOne::create ();
                listener->setSwallowTouches (true);
                listener->onTouchBegan = [this](Touch* touch,Event* event){
                    CCLog("onTouchBegan..............");
                     //this->setScaleY (1);

                    int tag = event->getCurrentTarget ()->getTag ();
                    std::string name = event->getCurrentTarget ()->getName ();
                    return true;
                };
                listener->onTouchMoved = [this](Touch* touch, Event* event){
                    float x = touch->getLocation ().x;
                    float y = touch->getLocation().y;
                    float x1 = touch->getStartLocation ().x;
                    float y1 = touch->getStartLocation().y;
                    float angle = CC_RADIANS_TO_DEGREES(-touch->getLocation ().getAngle (this->getPosition ()));
                    float distanceY = y1-y;
                    float distanceX = x1-x;
                    float scalY = distanceY/this->getBoundingBox ().size.height;


                    if((1+scalY) >0 && this->getScaleY ()<=2){
                         this->setScaleY (1+scalY);
                    }
                    this->setRotation (angle);


                    log("onTouchMoved..............x:%f, y:%f, x1:%f, y1:%f,  scalY:%f, angle:%f",x,y,x1,y1,scalY,angle);
                };
                listener->onTouchEnded = [this](Touch* touch,Event* event){
                    this->setScaleY (1);
                };

            _eventDispatcher->addEventListenerWithSceneGraphPriority (listener,this);
}

MySprite* MySprite::create (const std::string &filename)
{

        MySprite *sprite = new (std::nothrow) MySprite();
        if (sprite && sprite->init())
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;

}

MySprite* MySprite::create (const std::string& filename, const Rect& rect)
{

    MySprite *sprite = new (std::nothrow) MySprite();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();

        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
