#include <private/ege/glfw/keyboard.hxx>

namespace ege
{
    namespace glfw
    {
        Keyboard::Keyboard(const Window& window):
            window(window)
        {
            glfwSetKeyCallback(window.glfwWindowHandle, [](GLFWwindow* glfwWindow, int key, int scanCode, int action, int modifier)
                {
                    glfw::Keyboard* keyboard = &((glfw::Window*) glfwGetWindowUserPointer(glfwWindow))->getKeyboard();

                    switch (action)
                    {
                        case GLFW_PRESS:
                        {
                            for (keyboard::Listener* listener : keyboard->listeners)
                                listener->onKeyPress((keyboard::Key) key, keyboard::Modifier((unsigned int) modifier));

                            break;
                        }

                        case GLFW_RELEASE:
                        {
                            for (keyboard::Listener* listener : keyboard->listeners)
                                listener->onKeyRelease((keyboard::Key) key, keyboard::Modifier((unsigned int) modifier));

                            break;
                        }

                        default:
                            break;
                    }
                });
        }

        Keyboard::~Keyboard()
        {
            listeners.clear();
        }

        bool Keyboard::isPressed(keyboard::Key key) const
        {
            return glfwGetKey(window.glfwWindowHandle, (int) key) == GLFW_PRESS;
        }

        void Keyboard::addListener(keyboard::Listener* listener)
        {
            listeners.insert(listener);
        }

        void Keyboard::removeListener(keyboard::Listener* listener)
        {
            listeners.erase(listener);
        }
    }
}
