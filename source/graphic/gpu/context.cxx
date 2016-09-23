#include <ege/graphic/gpu/context.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace ege::graphic::gpu;


Context::Context( const hardware::monitor::VideoMode& videoMode ): defaultFrameBuffer( new FrameBuffer( 0 ) )
{
        defaultFrameBuffer->width = videoMode.width;
        defaultFrameBuffer->height = videoMode.height;

        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
        GLFWmonitor* glfwMonitor = static_cast< GLFWmonitor* >( static_cast< const hardware::Monitor* >( &videoMode.monitor )->glfwMonitor );
        glfwContext = glfwCreateWindow( videoMode.width, videoMode.height, "", glfwMonitor, NULL );

        glfwMakeContextCurrent( static_cast< GLFWwindow* >( glfwContext ) );
        glfwSwapInterval( 1 );

        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();
}


void Context::swapBuffers() const
{
        glfwSwapBuffers( static_cast< GLFWwindow* >( glfwContext ) );
}


Context::~Context()
{
        glfwDestroyWindow( static_cast< GLFWwindow* >( glfwContext ) );
        delete defaultFrameBuffer;
}


const FrameBuffer& Context::getDefaultFrameBuffer() const
{
        return *defaultFrameBuffer;
}


void Context::makeCurrentOnThisThread() const
{
        glfwMakeContextCurrent( static_cast< GLFWwindow* >( glfwContext ) );
}
