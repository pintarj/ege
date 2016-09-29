#include <ege/graphic/gpu/texture/texture-2D.hxx>
#include <GL/glew.h>
#include <cstddef>


using namespace ege::graphic::gpu::texture;


Texture2D::Texture2D( const util::ImageBuffer& imageBuffer, texture::Format format ):
        TwoDimensionalTexture( GL_TEXTURE_2D, imageBuffer, format )
{

}


Texture2D::Texture2D( const util::ImageBuffer& imageBuffer ):
        TwoDimensionalTexture( GL_TEXTURE_2D, imageBuffer )
{

}


Texture2D::Texture2D( unsigned int width, unsigned int height, texture::Format format ):
        TwoDimensionalTexture( GL_TEXTURE_2D, width, height, format )
{

}


Texture2D::~Texture2D()
{

}
