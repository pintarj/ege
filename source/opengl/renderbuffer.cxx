#include <ege/opengl/renderbuffer.hxx>
#include <GL/glew.h>

/*
 * The current implementation requires following OpenGL extensions:
 *      - GL_ARB_direct_state_access
 * */

namespace ege
{
    namespace opengl
    {
        Renderbuffer::Renderbuffer(int width, int height, RenderbufferInternalFormat internalFormat, int samples):
            Object([]() -> unsigned int
                {
                    unsigned int id;
                    glCreateRenderbuffers(1, &id);
                    return id;
                }()),
            width(width),
            height(height)
        {
            glNamedRenderbufferStorageMultisample(id, samples, (GLenum) internalFormat, width, height);
        }

        Renderbuffer::~Renderbuffer()
        {
            glDeleteRenderbuffers(1, &id);
        }
    }
}