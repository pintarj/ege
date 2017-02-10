
#ifndef EGE_GLFW_OPENGL_DEFAULT_FBO_HXX
#define EGE_GLFW_OPENGL_DEFAULT_FBO_HXX

namespace ege
{
    namespace glfw
    {
        class OpenGLDefaultFBO;
    }
}

#include <ege/opengl/framebuffer.hxx>
#include <private/ege/glfw/opengl-context.hxx>

namespace ege
{
    namespace glfw
    {
        /**
         * \brief Represent an OpenGL default framebuffer created by GLFW.
         * */
        class OpenGLDefaultFBO: public opengl::DefaultFramebuffer
        {
            public:
                /**
                 * \brief The context to which \c this is associated with.
                 * */
                const OpenGLContext& context;

                /**
                 * \brief Create a wrapper for the default framebuffer of the specified context.
                 * \param context The context of \c this framebuffer.
                 * */
                OpenGLDefaultFBO(const OpenGLContext& context);

                OpenGLDefaultFBO(OpenGLDefaultFBO&&) = delete;
                OpenGLDefaultFBO(const OpenGLDefaultFBO&) = delete;
                virtual ~OpenGLDefaultFBO() {}

                /**
                 * \brief Return the current dimensions of the framebuffer.
                 * \return A pair, where \c first is width of the framebuffer and \c second is the
                 *      height of the framebuffer.
                 */
                virtual std::pair<int, int> getSize();
        };
    }
}

#endif
