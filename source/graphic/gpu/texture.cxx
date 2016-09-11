#include <ege/graphic/gpu/texture.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


static inline unsigned int createTexture()
{
        unsigned int id;
        glGenTextures( 1, &id );
        return id;
}


Texture::Texture( unsigned int type, texture::Format format ): Object( createTexture() ), type( type ), format( format )
{

}


Texture::~Texture()
{
        glDeleteTextures( 1, &id );
}


void Texture::bindAtUnit( unsigned int index ) const
{
        glActiveTexture( GL_TEXTURE0 + index );
        glBindTexture( type, id );
}
