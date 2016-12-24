#include <ege/hardware/monitor.hxx>
#include <ege/exception.hxx>
#include <GLFW/glfw3.h>


using namespace ege;
using namespace ege::hardware;


monitor::VideoMode::VideoMode( unsigned int width, unsigned int height, unsigned int refreshRate, const Monitor& monitor ):
        width( width ), height( height ), refreshRate( refreshRate ), monitor( monitor )
{

}

void Monitor::createGPUContext( const hardware::monitor::VideoMode& videoMode )
{
        if ( const_cast< const Monitor* >( this ) != &videoMode.monitor )
                ege::exception::throwNew( "video mode is not owned by this monitor" );

        context = new graphic::gpu::Context( videoMode );
}


void Monitor::createGPUContext()
{
        createGPUContext( getCurrentVideoMode() );
}


Monitor::Monitor( void* glfwMonitor ): glfwMonitor( glfwMonitor )
{
        int indexOfCurrentVideoMode = -1;
        const GLFWvidmode* glfwVideoModes = glfwGetVideoModes( static_cast< GLFWmonitor* >( glfwMonitor ), ( int* ) &videoModesCount );
        const GLFWvidmode* glfwCurrentVideoMode = glfwGetVideoMode( static_cast< GLFWmonitor* >( glfwMonitor ) );
        videoModes = new hardware::monitor::VideoMode*[ videoModesCount ];

        for ( unsigned int i = 0; i < videoModesCount; ++i )
        {
                const GLFWvidmode* glfwVideoMode = &glfwVideoModes[ i ];
                const int width = glfwVideoMode->width;
                const int height = glfwVideoMode->height;
                const int refreshRate = glfwVideoMode->refreshRate;

                videoModes[ i ] = new hardware::monitor::VideoMode( ( unsigned int ) width, ( unsigned int ) height, ( unsigned int ) refreshRate, *this );

                if ( glfwCurrentVideoMode->width == width &&
                     glfwCurrentVideoMode->height == height &&
                     glfwCurrentVideoMode->refreshRate == refreshRate &&
                     glfwCurrentVideoMode->redBits == glfwVideoMode->redBits &&
                     glfwCurrentVideoMode->greenBits == glfwVideoMode->greenBits &&
                     glfwCurrentVideoMode->blueBits == glfwVideoMode->blueBits )
                {
                        indexOfCurrentVideoMode = i;
                }
        }

        if ( indexOfCurrentVideoMode == -1 )
                ege::exception::throwNew( "no current video mode found for monitor" );

        this->context = nullptr;
        this->current = videoModes[ indexOfCurrentVideoMode ];
}


Monitor::~Monitor()
{
        if ( this->context != nullptr )
                delete this->context;

        for ( unsigned int i = 0; i < videoModesCount; ++i )
                delete videoModes[ i ];

        delete[] videoModes;
}


const graphic::gpu::Context& Monitor::getGPUContext() const
{
        if ( context == nullptr )
                ege::exception::throwNew( "no GPU context found for this monitor" );

        return *context;
}


const monitor::VideoMode*& Monitor::getVideoModes( unsigned int* count ) const
{
        if ( count != nullptr )
                *count = videoModesCount;

        return *( const_cast< const hardware::monitor::VideoMode** >( videoModes ) );
}


const monitor::VideoMode& Monitor::getCurrentVideoMode() const
{
        return *current;
}
