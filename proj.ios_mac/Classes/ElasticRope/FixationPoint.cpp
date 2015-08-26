#include "FixationPoint.h"
namespace ElasticRopeBox2d {
    bool FixationPoint::init(){

        return true;
    }
    void FixationPoint::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
    {
        DrawPrimitives::setDrawColor4B(_color_r,_color_g,_color_b,_color_a);
        DrawPrimitives::drawSolidCircle(Point(0,0),_radius,M_PI*2,200);
       // DrawPrimitives::drawCircle(Point(0,0),50,M_PI*2,30,true);
    }
    void FixationPoint::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {
        this->_color_a = a;
        this->_color_b = b;
        this->_color_g = g;
        this->_color_r = r;
    }
    void FixationPoint::setRadius(float r){
        this->_radius = r;
    }

}
