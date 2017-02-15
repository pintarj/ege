#include <ege/opengl/viewport.hxx>
#include <GL/glew.h>

namespace ege
{
    namespace opengl
    {
        void viewport(int x, int y, int width, int height)
        {
            glViewport(x, y, width, height);
        }
    }
}
