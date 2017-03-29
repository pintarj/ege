#include <ege/opengl/blending.hxx>
#include <cassert>
#include <GL/glew.h>

namespace ege
{
    namespace opengl
    {
        void enableBlending() noexcept
        {
            glEnable(GL_BLEND);
        }

        void disableBlending() noexcept
        {
            glDisable(GL_BLEND);
        }

        void setBlendFunction(BlendFactor source, BlendFactor destination) noexcept
        {
            glBlendFunc((GLenum) source, (GLenum) destination);
        }
    }
}

class EgeOpenglBlendingTest
{
    public:
        EgeOpenglBlendingTest()
        {
            using namespace ege::opengl;
            assert(GL_ZERO == (GLenum) BlendFactor::ZERO);
            assert(GL_ONE == (GLenum) BlendFactor::ONE);
            assert(GL_SRC_COLOR == (GLenum) BlendFactor::SRC_COLOR);
            assert(GL_ONE_MINUS_SRC_COLOR == (GLenum) BlendFactor::ONE_MINUS_SRC_COLOR);
            assert(GL_DST_COLOR == (GLenum) BlendFactor::DST_COLOR);
            assert(GL_ONE_MINUS_DST_COLOR == (GLenum) BlendFactor::ONE_MINUS_DST_COLOR);
            assert(GL_SRC_ALPHA == (GLenum) BlendFactor::SRC_ALPHA);
            assert(GL_ONE_MINUS_SRC_ALPHA == (GLenum) BlendFactor::ONE_MINUS_SRC_ALPHA);
            assert(GL_DST_ALPHA == (GLenum) BlendFactor::DST_ALPHA);
            assert(GL_ONE_MINUS_DST_ALPHA == (GLenum) BlendFactor::ONE_MINUS_DST_ALPHA);
            assert(GL_CONSTANT_COLOR == (GLenum) BlendFactor::CONSTANT_COLOR);
            assert(GL_ONE_MINUS_CONSTANT_COLOR == (GLenum) BlendFactor::ONE_MINUS_CONSTANT_COLOR);
            assert(GL_CONSTANT_ALPHA == (GLenum) BlendFactor::CONSTANT_ALPHA);
            assert(GL_ONE_MINUS_CONSTANT_ALPHA == (GLenum) BlendFactor::ONE_MINUS_CONSTANT_ALPHA);
            assert(GL_SRC_ALPHA_SATURATE == (GLenum) BlendFactor::SRC_ALPHA_SATURATE);
        }

}
static ege_opengl_blending_test;
