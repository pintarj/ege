#include <ege/graphic/gpu/texture/util/image-buffer.hxx>


using namespace ege::graphic::gpu;
using namespace ege::graphic::gpu::texture::util;


ImageBuffer::ImageBuffer( unsigned int width, unsigned int height, imageBuffer::Format format, std::shared_ptr< gpu::Buffer > buffer, unsigned int offset ):
        width( width ), height( height ), format( format ), buffer( buffer )
{
        this->offset = offset;
}


ImageBuffer::~ImageBuffer()
{

}


const Buffer& ImageBuffer::getBuffer() const
{
        return *buffer;
}


unsigned int ImageBuffer::getInBufferOffset() const
{
        return offset;
}
