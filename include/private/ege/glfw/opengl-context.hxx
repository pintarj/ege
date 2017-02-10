
#ifndef EGE_GLFW_CONTEXT_HXX
#define EGE_GLFW_CONTEXT_HXX

namespace ege
{
    namespace glfw
    {
        class OpenGLContext;
    }
}

#include <memory>
#include <GLFW/glfw3.h>
#include <ege/opengl/context.hxx>
#include <private/ege/glfw/opengl-default-fbo.hxx>
#include <private/ege/glfw/window.hxx>

namespace ege
{
    namespace glfw
    {
        /**
         * \brief Represent an OpenGL context created by GLFW.
         * */
        class OpenGLContext: public opengl::Context
        {
            private:
                /**
                 * \brief The default framebuffer associated with the context.
                 * */
                std::unique_ptr<OpenGLDefaultFBO> defaultFBO;

            public:
                /**
                 * \brief The Window to which the context is associated with.
                 * */
                const Window& window;

                /**
                 * \brief Create a wrapper for the context of the specified Window.
                 * */
                OpenGLContext(const Window& window);

                OpenGLContext(OpenGLContext&&) = delete;
                OpenGLContext(const OpenGLContext&) = delete;
                virtual ~OpenGLContext() {}

                /**
                 * \brief Make \c this context current on the calling thread.
                 * */
                void makeCurrentOnThisThread() const;

                /**
                 * \brief Swap the front and the back buffer.
                 * */
                void swapBuffers() const;

                /**
                 * \brief Returns the default framebuffer associated with \c this context.
                 * \return The default framebuffer wrapper object.
                 * */
                virtual opengl::DefaultFramebuffer& getDefaultFramebuffer();
        };
    }
}

#endif
