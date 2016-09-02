#include <ege/hardware/monitor.hxx>


using namespace ege::hardware;


Monitor::Monitor( size_t width, size_t height )
{
        this->width = width;
        this->height = height;
}


void Monitor::getDimensions( size_t* width, size_t* height )
{
        *width = this->width;
        *height = this->height;
}


size_t Monitor::getFrameBufferId()
{
        return 0;
}
