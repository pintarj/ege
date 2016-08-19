#include <ege/graphic/step/clear.hxx>
#include <GL/glew.h>


using namespace ege::graphic::step;


void Clear::setClearColor( float r, float g, float b, float a )
{
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
}


void Clear::perform()
{
        glClearColor( r, g, b, a );
        glClear( GL_COLOR_BUFFER_BIT );
}
