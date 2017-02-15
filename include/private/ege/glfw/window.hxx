
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
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/hardware/monitor.hxx>
#include <private/ege/glfw/keyboard.hxx>
#include <private/ege/glfw/opengl-context.hxx>

namespace ege
{
    namespace glfw
    {
        /**
         * \brief A GLFW window.
         * */
        class Window
        {
            private:
                /**
                 * \brief The context associated with the window.
                 * */
                std::unique_ptr<OpenGLContext> context;

                /**
                 * \brief The keyboard associated with the window.
                 * */
                std::unique_ptr<glfw::Keyboard> keyboard;

                /**
                 * \brief Common sub-constructor for all public constructors.
                 * \param glfwWindowHandle The generated window handle.
                 * */
                Window(GLFWwindow* const glfwWindowHandle);

            public:
                /**
                 * \brief The GLFW handle value to manipulate window.
                 * */
                GLFWwindow* const glfwWindowHandle;

                /**
                 * \brief Create a fullscreen window using the specified video mode.
                 * \param title The window title.
                 * \param videoMode The specified video mode (his monitor will be used).
                 * */
                Window(const std::string& title, const hardware::VideoMode& videoMode);

                /**
                 * \brief Create a window of specified width and height.
                 * \param title The window title.
                 * \param width The window width.
                 * \param height The window height.
                 * \param resizable Indicate if the window should be resizable or not.
                 * */
                Window(const std::string& title, int width, int height, bool resizable = true);

                virtual ~Window();

                /**
                 * \brief Swap the front and the back buffer.
                 * */
                void swapBuffers() const;

                /**
                 * \brief Show the window (if it's hidden).
                 * */
                void show();

                /**
                 * \brief Get the OpenGL context associated with \c this Window.
                 * \return The OpenGL context.
                 * */
                OpenGLContext& getContext() const;

                /**
                 * \brief Get the keyboard associated with \c this Window.
                 * \return The keyboard.
                 * */
                glfw::Keyboard& getKeyboard() const;

                /**
                 * \brief Tells if Window should be closed.
                 * \return \c True if it should be closed.
                 *
                 * For example if alt+F4 is pressed, this method returns \c true.
                 * */
                bool shouldClose() const;
        };
    }
}

#endif
