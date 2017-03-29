#include <ege/opengl/rasterization.hxx>
#include <GL/glew.h>

namespace ege
{
    namespace opengl
    {
        void enableLineSmooth() noexcept
        {
            glEnable(GL_LINE_SMOOTH);
        }

        void disableLineSmooth() noexcept
        {
            glDisable(GL_LINE_SMOOTH);
        }

        void enablePolygonSmooth() noexcept
        {
            glEnable(GL_POLYGON_SMOOTH);
        }

        void disablePolygonSmooth() noexcept
        {
            glDisable(GL_POLYGON_SMOOTH);
        }
    }
}
