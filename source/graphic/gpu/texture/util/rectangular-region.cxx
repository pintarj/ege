#include <ege/graphic/gpu/texture/util/rectangular-region.hxx>


using namespace ege::graphic::gpu::texture::util;


RectangularRegion::RectangularRegion( const Texture2D &texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height ):
        texture( texture ), width( width ), height( height ), x( x ), y( y )
{
        recalculateUV();
}


RectangularRegion::RectangularRegion( const Texture2D &texture ): RectangularRegion( texture, 0, 0, texture.width, texture.height )
{

}


void RectangularRegion::recalculateUV()
{
        const float tw = ( float ) texture.width;
        const float th = ( float ) texture.height;
        const float fx = ( float ) x;
        const float fy = ( float ) y;
        const float fw = ( float ) width;
        const float fh = ( float ) height;
        const float lx = fx / tw;
        const float rx = ( fx + fw ) / tw;
        const float by = ( fy / th );
        const float ty = ( fy + fh ) / th;

        uv[ 0 ] = lx;
        uv[ 1 ] = by;
        uv[ 2 ] = lx;
        uv[ 3 ] = ty;
        uv[ 4 ] = rx;
        uv[ 5 ] = by;
        uv[ 6 ] = rx;
        uv[ 7 ] = ty;
}


const float* RectangularRegion::getUVCoordinates() const
{
        return uv;
}
