#include <private/ege/glfw/opengl-context.hxx>

namespace ege
{
    namespace glfw
    {
        OpenGLContext::OpenGLContext(const Window& window):
            defaultFBO(new OpenGLDefaultFBO(*this)),
            window(window)
        {

        }

        void OpenGLContext::makeCurrentOnThisThread() const
        {
            glfwMakeContextCurrent((GLFWwindow*) window.glfwWindowHandle);
        }

        void OpenGLContext::swapBuffers() const
        {
            glfwSwapBuffers((GLFWwindow*) window.glfwWindowHandle);
        }

        opengl::DefaultFramebuffer& OpenGLContext::getDefaultFramebuffer()
        {
            return *defaultFBO;
        }
    }
}
