#include <ege/graphic/texture/pixels-buffer.hxx>


using namespace ege::graphic;
using namespace ege::graphic::texture;


PixelsBuffer::PixelsBuffer( size_t width, size_t height, gpu::Buffer& pixels, Format format, bool deleteBuffer ):
        width( width ), height( height ), pixels( pixels ), format( format ), deleteBuffer( deleteBuffer )
{

}


PixelsBuffer::PixelsBuffer( size_t width, size_t height, const void* pixels, Format format ):
        PixelsBuffer( width, height, *new gpu::Buffer( width * height * format::bytesPerPixel( format ), pixels, gpu::BufferUsage::STATIC ), format, true )
{

}


PixelsBuffer::~PixelsBuffer()
{
        if ( deleteBuffer )
                delete &pixels;
}


void PixelsBuffer::getDimensions( size_t* width, size_t* height )
{
        *width = this->width;
        *height = this->height;
}


gpu::Buffer& PixelsBuffer::getPixels()
{
        return pixels;
}


const Format PixelsBuffer::getFormat()
{
        return format;
}


