#include <ege/graphic/gpu/texture/two-dimensional-texture.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu::texture;


TwoDimensionalTexture::TwoDimensionalTexture( unsigned int type, const util::ImageBuffer& imageBuffer, Format format ):
        Texture( type, format ), width( imageBuffer.width ), height( imageBuffer.height )
{
        glBindTexture( type, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, object::getId( imageBuffer.getBuffer() ) );
        const void* offset = reinterpret_cast< const void* >( ( size_t ) imageBuffer.getInBufferOffset() );
        glTexImage2D( type, 0, ( GLenum ) format, width, height, 0, ( GLenum ) imageBuffer.format, GL_UNSIGNED_BYTE, offset );
}


TwoDimensionalTexture::TwoDimensionalTexture( unsigned int type, const util::ImageBuffer& imageBuffer ):
        TwoDimensionalTexture( type, imageBuffer, static_cast< Format >( static_cast< GLenum >( imageBuffer.format ) ) )
{

}


TwoDimensionalTexture::TwoDimensionalTexture( unsigned int type, unsigned int width, unsigned int height, Format format ):
        Texture( type, format ), width( width ), height( height )
{
        glBindTexture( type, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        glTexImage2D( type, 0, ( GLenum ) format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
}


TwoDimensionalTexture::~TwoDimensionalTexture()
{

}


unsigned int TwoDimensionalTexture::getWidth() const
{
        return width;
}


unsigned int TwoDimensionalTexture::getHeight() const
{
        return height;
}


void TwoDimensionalTexture::substitute( unsigned int x, unsigned int y, const util::ImageBuffer& imageBuffer )
{
        glBindTexture( type, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, object::getId( imageBuffer.getBuffer() ) );
        const void* offset = reinterpret_cast< const void* >( ( size_t ) imageBuffer.getInBufferOffset() );
        glTexSubImage2D( type, 0, x, y, imageBuffer.width, imageBuffer.height, ( GLenum ) imageBuffer.format, GL_UNSIGNED_BYTE, offset );
}
