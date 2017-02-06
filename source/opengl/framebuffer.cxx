#include <ege/opengl/framebuffer.hxx>
#include <GL/glew.h>

namespace ege
{
    namespace opengl
    {
        Framebuffer::Framebuffer(unsigned int id):
            Object(id)
        {

        }

        Framebuffer::Framebuffer():
            Framebuffer([]() -> unsigned int
            {
                unsigned int id;
                glCreateFramebuffers(1, &id);
                return id;
            }())
        {

        }

        Framebuffer::~Framebuffer()
        {
            if (!isDefault())
                glDeleteFramebuffers(1, &id);
        }

        void Framebuffer::bind() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, id);
        }

        void Framebuffer::attachRenderbuffer(FBOAttachment attachment, Renderbuffer& renderbuffer)
        {
            glNamedFramebufferRenderbuffer(id, (unsigned int) attachment, GL_RENDERBUFFER, renderbuffer.id);
        }

        bool Framebuffer::isDefault() const
        {
            return id == 0;
        }

        void Framebuffer::clearColor(unsigned index, const float* values)
        {
            glClearNamedFramebufferfv(id, GL_COLOR, index, values);
        }

        void Framebuffer::clearColor(unsigned index, float r, float g, float b, float a)
        {
            const float values[] = {r, g, b, a};
            clearColor(index, values);
        }

        void Framebuffer::clearDepth(float depth)
        {
            glClearNamedFramebufferfv(id, GL_DEPTH, 0, &depth);
        }

        void Framebuffer::clearStencil(int stencil)
        {
            glClearNamedFramebufferiv(id, GL_STENCIL, 0, &stencil);
        }

        void Framebuffer::invalidate(FramebufferAttachment attachment)
        {
            const GLenum attachments[] = {(GLenum) attachment};
            glInvalidateNamedFramebufferData(id, 1, attachments);
        }

        void Framebuffer::blitFrom(const opengl::Framebuffer& source, int srcX0, int srcY0, int srcX1, int srcY1,
                int dstX0, int dstY0, int dstX1, int dstY1, FBOBuffer target, Filter filter)
        {
            glBlitNamedFramebuffer(source.id, id, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,
                (GLenum) target, (GLenum) filter);
        }

        void clear(FBOBuffer target)
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

        void setClearStencil(int s)
        {
            glClearStencil(s);
        }
    }
}
