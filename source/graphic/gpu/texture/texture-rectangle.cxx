#include <ege/graphic/gpu/texture/texture-rectangle.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu::texture;


TextureRectangle::TextureRectangle( const util::ImageBuffer& imageBuffer, Format format ):
        TwoDimensionalTexture( Type::RECTANGLE, imageBuffer, format )
{

}


TextureRectangle::TextureRectangle( const util::ImageBuffer& imageBuffer ):
        TwoDimensionalTexture( Type::RECTANGLE, imageBuffer )
{

}


TextureRectangle::TextureRectangle( unsigned int width, unsigned int height, Format format ):
        TwoDimensionalTexture( Type::RECTANGLE, width, height, format )
{

}


TextureRectangle::~TextureRectangle()
{

}
