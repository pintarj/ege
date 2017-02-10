
#ifndef EGE_GLFW_WINDOW_HXX
#define EGE_GLFW_WINDOW_HXX

namespace ege
{
    namespace glfw
    {
        class Window;
    }
}

#include <memory>
#include <GLFW/glfw3.h>
#include <private/ege/glfw/opengl-context.hxx>

namespace ege
{
    namespace glfw
    {
        class Window
        {
            private:
                std::unique_ptr<OpenGLContext> context;

            public:
                GLFWwindow* const glfwWindowHandle;

                Window();
                virtual ~Window();
        };
    }
}

#endif
