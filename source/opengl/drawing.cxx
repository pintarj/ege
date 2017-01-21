#include <ege/opengl/drawing.hxx>
#include <GL/glew.h>

/*
 * The current implementation requires following OpenGL requirements:
 *      - OpenGL 3.1+
 *      - GL_ARB_base_instance
 * */

namespace ege
{
    namespace opengl
    {
        void drawArrays(DrawMode mode, int first, int count)
        {
            glDrawArrays((GLenum) mode, first, count);
        }

        void drawArraysInstanced(DrawMode mode, int first, int count, int instanceCount)
        {
            glDrawArraysInstanced((GLenum) mode, first, count, instanceCount);
        }

        void drawArraysInstancedBaseInstance(DrawMode mode, int first, int count, int instanceCount, unsigned int baseInstance)
        {
            glDrawArraysInstancedBaseInstance((GLenum) mode, first, count, instanceCount, baseInstance);
        }

        void multiDrawArrays(DrawMode mode, int* first, int* count, int drawCount)
        {
            glMultiDrawArrays((GLenum) mode, first, count, drawCount);
        }
    }
}
