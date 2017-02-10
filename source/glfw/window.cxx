#include <private/ege/glfw/window.hxx>

namespace ege
{
    namespace glfw
    {
        Window::Window():
            glfwWindowHandle([]() -> GLFWwindow*
                {
                    GLFWmonitor* primary = glfwGetPrimaryMonitor();
                    const GLFWvidmode* videoMode = glfwGetVideoMode(primary);
                    glfwDefaultWindowHints();
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                    glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
                    glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
                    glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
                    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "", primary, NULL);
                    return window;
                }())
        {

        }

        Window::~Window()
        {
            glfwDestroyWindow(glfwWindowHandle);
        }
    }
}
