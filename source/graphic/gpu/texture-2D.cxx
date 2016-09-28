#include <ege/graphic/gpu/texture-2D.hxx>
#include <GL/glew.h>
#include <cstddef>


using namespace ege::graphic::gpu;


Texture2D::Texture2D( const util::image::Buffer& imageBuffer, texture::Format format ):
        Texture( GL_TEXTURE_2D, format ), width( imageBuffer.width ), height( imageBuffer.height )
{
        glBindTexture( GL_TEXTURE_2D, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, object::getId( imageBuffer.getBuffer() ) );
        const void* offset = reinterpret_cast< const void* >( ( size_t ) imageBuffer.getInBufferOffset() );
        glTexImage2D( GL_TEXTURE_2D, 0, ( GLenum ) format, width, height, 0, ( GLenum ) imageBuffer.format, GL_UNSIGNED_BYTE, offset );
}


Texture2D::Texture2D( const util::image::Buffer& imageBuffer ): Texture2D( imageBuffer, ( texture::Format ) ( ( GLenum ) imageBuffer.format ) )
{

}


Texture2D::Texture2D( unsigned int width, unsigned int height, texture::Format format ):
        Texture( GL_TEXTURE_2D, format ), width( width ), height( height )
{
        glBindTexture( GL_TEXTURE_2D, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        glTexImage2D( GL_TEXTURE_2D, 0, ( GLenum ) format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
}


Texture2D::~Texture2D()
{

}
