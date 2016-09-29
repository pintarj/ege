#include <ege/graphic/gpu/texture/util/rectangular-region.hxx>


using namespace ege::graphic::gpu::texture;
using namespace ege::graphic::gpu::texture::util;


constexpr static bool recalculationCouldMakeSenseFor( Type type )
{
        switch ( type )
        {
                case Type::TEX_2D:
                        return true;

                case Type::RECTANGLE:
                        return false;
        }
}


RectangularRegion::RectangularRegion( const TwoDimensionalTexture &texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool recalculationCouldMakeSense ):
        texture( texture ), width( width ), height( height ), x( x ), y( y ), recalculationCouldMakeSense( recalculationCouldMakeSense )
{
        calculateUV();
}


void RectangularRegion::calculateUV()
{
        float lx = ( float ) x;
        float rx = lx + ( float ) width;
        float by = ( float ) y;
        float ty = by + ( float ) height;

        switch ( texture.type )
        {
                case Type::TEX_2D:
                {
                        const float tw = ( float ) texture.getWidth();
                        const float th = ( float ) texture.getHeight();

                        lx /= tw;
                        rx /= tw;
                        by /= th;
                        ty /= th;
                }

                default:
                        break;
        }

        uv[ 0 ] = lx;
        uv[ 1 ] = by;
        uv[ 2 ] = lx;
        uv[ 3 ] = ty;
        uv[ 4 ] = rx;
        uv[ 5 ] = by;
        uv[ 6 ] = rx;
        uv[ 7 ] = ty;
}


RectangularRegion::RectangularRegion( const TwoDimensionalTexture& texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height ):
        RectangularRegion( texture, x, y, width, height, recalculationCouldMakeSenseFor( texture.type ) )
{

}


RectangularRegion::RectangularRegion( const TwoDimensionalTexture &texture ):
        RectangularRegion( texture, 0, 0, texture.getWidth(), texture.getHeight(), true )
{

}


void RectangularRegion::recalculateUV()
{
        if ( recalculationCouldMakeSense )
                calculateUV();
}


const float* RectangularRegion::getUVCoordinates() const
{
        return uv;
}
