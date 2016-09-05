#include <ege/graphic/render/targetable.hxx>
#include <GL/glew.h>


using namespace ege::graphic::render;


void Targetable::setAsTarget()
{
        size_t width, height;
        getDimensions( &width, &height );
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, ( GLuint ) getFrameBufferId() );
        glViewport( 0, 0, ( GLuint ) width, ( GLuint ) height );
}
