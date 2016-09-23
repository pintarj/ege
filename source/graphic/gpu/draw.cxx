#include <ege/graphic/gpu/draw.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


void draw::arrays( Mode mode, unsigned int offset, unsigned int count )
{
        glDrawArrays( ( GLenum ) mode, offset, count );
}
