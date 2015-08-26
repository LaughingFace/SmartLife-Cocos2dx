#include "cocos2d.h"
USING_NS_CC;
namespace ElasticRopeBox2d {
    class FixationPoint : public Node{
    private:
        float _radius;
        GLubyte _color_r;
        GLubyte _color_g;
        GLubyte _color_b;
        GLubyte _color_a;


    public:

        void setColor(GLubyte r,GLubyte g,GLubyte b,GLubyte a);
        void setRadius(float r);
        virtual bool init();
        virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
        CREATE_FUNC(FixationPoint) ;
    };
}
