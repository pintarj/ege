#include <ege/graphic/texture/texture.hxx>
#include <GL/glew.h>


using namespace ege::graphic::texture;


Texture::Texture( size_t width, size_t height, const void* pixels )
{
        GLuint id;
        glGenTextures( 1, &id );
        glBindTexture( GL_TEXTURE_2D, id );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ( GLsizei ) width, ( GLsizei ) height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
        textureId = id;
        this->width = width;
        this->height = height;
        frameBufferId = 0;
}


size_t Texture::getTextureId()
{
        return textureId;
}


Texture::~Texture()
{
        GLuint id = ( GLuint ) textureId;
        glDeleteTextures( 1, &id );
}


void Texture::useAtUnit( size_t unit )
{
        glActiveTexture( GL_TEXTURE0 + ( GLuint ) unit );
        glBindTexture( GL_TEXTURE_2D, ( GLuint ) textureId );
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
