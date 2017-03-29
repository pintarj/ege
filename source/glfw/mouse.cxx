#include <private/ege/glfw/mouse.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ege
{
    namespace glfw
    {
        Mouse::Mouse(const Window& window):
            window(window)
        {
            auto callback = [](GLFWwindow* glfwWindow, double x, double y)
                {
                    glfw::Mouse* mouse = &((glfw::Window*) glfwGetWindowUserPointer(glfwWindow))->getMouse();

                    for (mouse::PositionListener* listener : mouse->positionListeners)
                        listener->onPositionChange(x, y);
                };

            glfwSetCursorPosCallback(window.glfwWindowHandle, callback);
        }

        Mouse::~Mouse()
        {
            positionListeners.clear();
        }

        void Mouse::getPosition(double* x, double* y) const
        {
            glfwGetCursorPos(window.glfwWindowHandle, x, y);
        }

        void Mouse::addPositionListener(mouse::PositionListener* listener)
        {
            positionListeners.insert(listener);
        }

        void Mouse::removePositionListener(mouse::PositionListener* listener)
        {
            positionListeners.erase(listener);
        }
    }
}
