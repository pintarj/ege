#include <ege/graphic/gpu/texture/two-dimensional-texture.hxx>
#include <GL/glew.h>
#include <cstddef>


using namespace ege::graphic::gpu::texture;


TwoDimensionalTexture::TwoDimensionalTexture( Type type, const util::ImageBuffer& imageBuffer, Format format ):
        Texture( type, format ), width( imageBuffer.width ), height( imageBuffer.height )
{
        glBindTexture( ( GLenum ) type, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, object::getId( imageBuffer.getBuffer() ) );
        const void* offset = reinterpret_cast< const void* >( ( size_t ) imageBuffer.getInBufferOffset() );
        glTexImage2D( ( GLenum ) type, 0, ( GLenum ) format, width, height, 0, ( GLenum ) imageBuffer.format, GL_UNSIGNED_BYTE, offset );
}


TwoDimensionalTexture::TwoDimensionalTexture( Type type, const util::ImageBuffer& imageBuffer ):
        TwoDimensionalTexture( type, imageBuffer, static_cast< Format >( static_cast< GLenum >( imageBuffer.format ) ) )
{

}


TwoDimensionalTexture::TwoDimensionalTexture( Type type, unsigned int width, unsigned int height, Format format ):
        Texture( type, format ), width( width ), height( height )
{
        glBindTexture( ( GLenum ) type, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        glTexImage2D( ( GLenum ) type, 0, ( GLenum ) format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
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
        glBindTexture( ( GLenum ) type, id );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, object::getId( imageBuffer.getBuffer() ) );
        const void* offset = reinterpret_cast< const void* >( ( size_t ) imageBuffer.getInBufferOffset() );
        glTexSubImage2D( ( GLenum ) type, 0, x, y, imageBuffer.width, imageBuffer.height, ( GLenum ) imageBuffer.format, GL_UNSIGNED_BYTE, offset );
}


void TwoDimensionalTexture::resize( unsigned int width, unsigned int height, unsigned int sourceX, unsigned int sourceY,
        unsigned int destinationX, unsigned int destinationY, unsigned int copyWidth, unsigned int copyHeight )
{
        const unsigned int bufferSize = this->width * this->height * 4;
        unsigned int bufferId;

        glGenBuffers( 1, &bufferId );
        glBindBuffer( GL_PIXEL_PACK_BUFFER, bufferId );
        glBufferData( GL_PIXEL_PACK_BUFFER, bufferSize, nullptr, GL_STREAM_COPY );
        glBindTexture( ( GLenum ) type, id );
        glGetTexImage( ( GLenum ) type, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        glTexImage2D( ( GLenum ) type, 0, ( GLenum ) format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, bufferId );

        for ( unsigned int i = 0; i < copyHeight; ++i )
        {
                void* offset = reinterpret_cast< void* >( static_cast< size_t >( ( sourceX + ( sourceY + i ) * this->width ) * 4 ) );
                glTexSubImage2D( ( GLenum ) type, 0, destinationX, destinationY + i, copyWidth, 1, GL_RGBA, GL_UNSIGNED_BYTE, offset );
        }

        glDeleteBuffers( 1, &bufferId );

        this->width = width;
        this->height = height;
}


void TwoDimensionalTexture::resize( unsigned int width, unsigned int height, bool keepData )
{
        if ( keepData )
        {
                const unsigned int copyWidth = ( width < this->width ) ? width : this->width;
                const unsigned int copyHeight = ( height < this->height ) ? height : this->height;
                resize( width, height, 0, 0, 0, 0, copyWidth, copyHeight );
        }
        else
        {
                glBindTexture( ( GLenum ) type, id );
                glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
                glTexImage2D( ( GLenum ) type, 0, ( GLenum ) format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
                this->width = width;
                this->height = height;
        }
}
