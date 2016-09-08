#include <ege/graphic/texture/pixels-buffer.hxx>


using namespace ege::graphic;
using namespace ege::graphic::texture;


PixelsBuffer::PixelsBuffer( size_t width, size_t height, buffer::Buffer& pixels, Format format, bool deleteBuffer ):
        width( width ), height( height ), pixels( pixels ), format( format ), deleteBuffer( deleteBuffer )
{

}


PixelsBuffer::PixelsBuffer( size_t width, size_t height, const void* pixels, Format format ):
        PixelsBuffer( width, height, *new buffer::Buffer( width * height * format::bytesPerPixel( format ), pixels, buffer::BufferUsage::STATIC ), format, true )
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


buffer::Buffer& PixelsBuffer::getPixels()
{
        return pixels;
}


const Format PixelsBuffer::getFormat()
{
        return format;
}


