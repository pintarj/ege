#include <ege/graphic/render/draw.hxx>
#include <GL/glew.h>


using namespace ege::graphic::render;


void draw::arrays( Mode mode, size_t offset, size_t count )
{
        glDrawArrays( ( GLenum ) mode, ( GLint ) offset, ( GLsizei ) count );
}
