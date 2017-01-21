#include <ege/opengl/clearing.hxx>
#include <GL/glew.h>

/*
 * The current implementation requires following OpenGL requirements:
 *      - OpenGL 4.1+
 * */

namespace ege
{
    namespace opengl
    {
        void clear(ClearTarget target)
        {
            glClear((GLenum) target);
        }

        void setClearColor(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);
        }

        void setClearDepth(float d)
        {
            glClearDepthf(d);
        }

        void setClearDepth(double d)
        {
            glClearDepth(d);
        }

        void setClearStencil(int s)
        {
            glClearStencil(s);
        }
    }
}
