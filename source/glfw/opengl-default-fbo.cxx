#include <private/ege/glfw/opengl-default-fbo.hxx>
#include <GLFW/glfw3.h>

namespace ege
{
    namespace glfw
    {
        OpenGLDefaultFBO::OpenGLDefaultFBO(const OpenGLContext& context):
            DefaultFramebuffer(),
            context(context)
        {

        }

        std::pair<int, int> OpenGLDefaultFBO::getSize()
        {
            int width, height;
            glfwGetFramebufferSize((GLFWwindow*) context.window.glfwWindowHandle, &width, &height);
            return std::pair<int, int>(width, height);
        }
    }
}
