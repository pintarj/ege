#include <ege/graphic/gpu/util/image/buffer.hxx>


using namespace ege::graphic::gpu::util::image;


Buffer::Buffer( unsigned int width, unsigned int height, buffer::Format format, std::shared_ptr< gpu::Buffer > buffer, unsigned int offset ):
        width( width ), height( height ), format( format ), buffer( buffer )
{
        this->offset = offset;
}


Buffer::~Buffer()
{

}


const ege::graphic::gpu::Buffer& Buffer::getBuffer() const
{
        return *buffer;
}


unsigned int Buffer::getInBufferOffset() const
{
        return offset;
}
