#include <ege/graphic/gpu/context.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/exception.hxx>


using namespace ege;
using namespace ege::graphic::gpu;


void context::blend::enable()
{
        glEnable( GL_BLEND );
}


void context::blend::disable()
{
        glDisable( GL_BLEND );
}


Context::Context( const hardware::monitor::VideoMode& videoMode ): defaultFrameBuffer( new FrameBuffer( 0 ) )
{
        defaultFrameBuffer->width = videoMode.width;
        defaultFrameBuffer->height = videoMode.height;

        int contextMajor = 4;
        int contextMinor = 1;

        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, contextMajor );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, contextMinor );
        GLFWmonitor* glfwMonitor = static_cast< GLFWmonitor* >( static_cast< const hardware::Monitor* >( &videoMode.monitor )->glfwMonitor );
        glfwContext = glfwCreateWindow( videoMode.width, videoMode.height, "", glfwMonitor, NULL );

        if ( glfwContext == nullptr )
                ege::exception::throwNew( "could not create OpenGL context" );

        engine::resources->logger->log( util::log::Level::INFO, "OpenGL %d.%d context created", contextMajor, contextMinor );

        glfwMakeContextCurrent( static_cast< GLFWwindow* >( glfwContext ) );
        glfwSwapInterval( 1 );

        glewExperimental = GL_TRUE;
        GLenum error = glewInit();
        glGetError();

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        if ( error != GLEW_OK )
                ege::exception::throwNew( "could not initialize GLEW: %s", glewGetErrorString( error ) );

        engine::resources->logger->log( util::log::Level::INFO, "GLEW %s initialized", glewGetString( GLEW_VERSION ) );
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
