#include <ege/opengl/hint.hxx>
#include <cassert>
#include <GL/glew.h>

namespace ege
{
    namespace opengl
    {
        void setHint(HintTarget target, Hint hint) noexcept
        {
            glHint((GLenum) target, (GLenum) hint);
        }
    }
}

class EgeOpenglHintTest
{
    public:
        EgeOpenglHintTest()
        {
            using namespace ege::opengl;
            assert(GL_LINE_SMOOTH_HINT == (GLenum) HintTarget::LINE_SMOOTH);
            assert(GL_POLYGON_SMOOTH_HINT == (GLenum) HintTarget::POLYGON_SMOOTH);
            assert(GL_TEXTURE_COMPRESSION_HINT == (GLenum) HintTarget::TEXTURE_COMPRESSION);
            assert(GL_FRAGMENT_SHADER_DERIVATIVE_HINT == (GLenum) HintTarget::FRAGMENT_SHADER_DERIVATIVE);
            assert(GL_FASTEST == (GLenum) Hint::FASTEST);
            assert(GL_NICEST == (GLenum) Hint::NICEST);
            assert(GL_DONT_CARE == (GLenum) Hint::DONT_CARE);
        }

}
static ege_opengl_hint_test;
