#ifndef MYSPRITE_H
#define MYSPRITE_H

#include "cocos2d.h"
#include "math.h"

USING_NS_CC;

class MySprite : public Sprite
{
public:
    MySprite();
    void prepare();
       static MySprite* create(const std::string& filename);
       static MySprite* create(const std::string& filename, const Rect& rect);



};

#endif // MYSPRITE_H
