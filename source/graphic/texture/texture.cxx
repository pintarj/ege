#include <ege/graphic/texture/texture.hxx>
#include <GL/glew.h>


using namespace ege::graphic::texture;


Texture::Texture( Format format ): format( format )
{
        GLuint id;
        glGenTextures( 1, &id );
        textureId = id;
}


Texture::Texture( PixelsBuffer &pixelsBuffer, bool deleteBuffer ): Texture( pixelsBuffer.getFormat() )
{
        pixelsBuffer.getDimensions( &width, &height );
        const GLenum format = ( GLenum ) pixelsBuffer.getFormat();
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, ( GLuint ) pixelsBuffer.getPixels().getBufferId() );
        glBindTexture( GL_TEXTURE_2D, ( GLuint ) textureId );
        glTexImage2D( GL_TEXTURE_2D, 0, format, ( GLsizei ) width, ( GLsizei ) height, 0, format, GL_UNSIGNED_BYTE, NULL );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        frameBufferId = 0;

        if ( deleteBuffer )
                delete &pixelsBuffer;
}


Texture::Texture( size_t width, size_t height, const void* pixels, Format format ):
        Texture( *new PixelsBuffer( width, height, pixels, format ), true )
{

}


Texture::Texture( size_t width, size_t height, Format format, bool willBeTargeted ): Texture( format )
{
        glBindTexture( GL_TEXTURE_2D, ( GLuint ) textureId );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, ( GLsizei ) width, ( GLsizei ) height, 0, ( GLuint ) format, GL_UNSIGNED_BYTE, nullptr );
        this->width = width;
        this->height = height;
        frameBufferId = 0;

        if ( willBeTargeted )
                prepareForTargeting();
}


size_t Texture::getTextureId()
{
        return textureId;
}


Texture::~Texture()
{
        GLuint id = ( GLuint ) textureId;
        glDeleteTextures( 1, &id );

        if ( frameBufferId != 0 )
        {
                id = ( GLint ) frameBufferId;
                glDeleteFramebuffers( 1, &id );
        }
}


void Texture::useAtUnit( size_t unit )
{
        glActiveTexture( GL_TEXTURE0 + ( GLuint ) unit );
        glBindTexture( GL_TEXTURE_2D, ( GLuint ) textureId );
}


Format Texture::getFormat()
{
        return format;
}


void Texture::prepareForTargeting()
{
        if ( frameBufferId != 0 )
                return;

        GLuint id;
        glGenFramebuffers( 1, &id );
        glBindFramebuffer( GL_READ_FRAMEBUFFER, id );
        glFramebufferTexture2D( GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ( GLuint ) textureId, 0 );
        frameBufferId = id;
}


size_t Texture::getWidth()
{
        return width;
}


size_t Texture::getHeight()
{
        return height;
}


void Texture::getDimensions( size_t* width, size_t* height )
{
        *width = this->width;
        *height = this->height;
}


size_t Texture::getFrameBufferId()
{
        return frameBufferId;
}
