#include <private/ege/glfw/window.hxx>
#include <ege/exception.hxx>
#include <ege/engine/resources.hxx>
#include <private/ege/glfw/monitor.hxx>

namespace ege
{
    namespace glfw
    {
        static const int targetContextMajor = 4;
        static const int targetContextMinor = 1;

        static inline void setGeneralHints()
        {
            glfwDefaultWindowHints();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, targetContextMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, targetContextMinor);
            glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
            glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
        }

        static inline void initializeGLEW()
        {
            glewExperimental = GL_TRUE;
            GLenum error = glewInit();
            glGetError();

            if (error != GLEW_OK)
                ege::exception::throwNew("could not initialize GLEW: %s", glewGetErrorString(error));

            engine::getLogger().log(log::Level::INFO, "GLEW %s initialized", glewGetString(GLEW_VERSION));
        }

        Window::Window(GLFWwindow* const glfwWindowHandle):
            glfwWindowHandle(glfwWindowHandle)
        {
            if (glfwWindowHandle == nullptr)
                exception::throwNew("could not create OpenGL context (or GLFW window)");

            glfwSetWindowUserPointer(glfwWindowHandle, this);
            keyboard = std::unique_ptr<glfw::Keyboard>(new glfw::Keyboard(*this));
            mouse = std::unique_ptr<glfw::Mouse>(new glfw::Mouse(*this));
            context = std::unique_ptr<OpenGLContext>(new OpenGLContext(*this));
            context->makeCurrentOnThisThread();
            glfwSwapInterval(1);
            initializeGLEW();
            engine::getLogger().log(log::Level::INFO, "OpenGL %d.%d context created", targetContextMajor, targetContextMinor);
        }

        Window::Window(const std::string& title, const hardware::VideoMode& videoMode):
            Window([&]() -> GLFWwindow*
                {
                    setGeneralHints();
                    glfwWindowHint(GLFW_RED_BITS, videoMode.redBits);
                    glfwWindowHint(GLFW_GREEN_BITS, videoMode.greenBits);
                    glfwWindowHint(GLFW_BLUE_BITS, videoMode.blueBits);
                    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
                    glfwWindowHint(GLFW_REFRESH_RATE, videoMode.refreshRate);
                    GLFWmonitor* monitor = (GLFWmonitor*) ((const glfw::Monitor*) &videoMode.monitor)->glfwMonitorHandle;
                    GLFWwindow* window = glfwCreateWindow(videoMode.width, videoMode.height, title.c_str(), monitor, NULL);
                    return window;
                }())
        {

        }

        Window::Window(const std::string& title, int width, int height, bool resizable):
            Window([&]() -> GLFWwindow*
                {
                    setGeneralHints();
                    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
                    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
                    return window;
                }())
        {

        }

        Window::~Window()
        {
            glfwDestroyWindow(glfwWindowHandle);
        }

        void Window::swapBuffers() const
        {
            context->swapBuffers();
        }

        void Window::show()
        {
            glfwShowWindow(glfwWindowHandle);
        }

        OpenGLContext& Window::getContext() const noexcept
        {
            return *context.get();
        }

        glfw::Keyboard& Window::getKeyboard() const noexcept
        {
            return *keyboard.get();
        }

        glfw::Mouse& Window::getMouse() const noexcept
        {
            return *mouse.get();
        }

        bool Window::shouldClose() const
        {
            return glfwWindowShouldClose(glfwWindowHandle) != 0;
        }
    }
}
