#include <ege/graphic/texture/rectangular-region.hxx>


using namespace ege::graphic::texture;


RectangularRegion::RectangularRegion( Texture &texture, size_t x, size_t y, size_t width, size_t height ): Region( texture )
{
        size_t texCoord[ 2 ];
        texture.getDimensions( &texCoord[ 0 ], &texCoord[ 1 ] );
        const float tw = ( float ) texCoord[ 0 ];
        const float th = ( float ) texCoord[ 1 ];
        const float fx = ( float ) x;
        const float fy = ( float ) y;
        const float fw = ( float ) width;
        const float fh = ( float ) height;
        const float lx = fx / tw;
        const float rx = ( fx + fw ) / tw;
        const float by = 1.0f - ( fy / th );
        const float ty = 1.0f - ( ( fy + fh ) / th );

        uv[ 0 ] = lx;
        uv[ 1 ] = ty;
        uv[ 2 ] = lx;
        uv[ 3 ] = by;
        uv[ 4 ] = rx;
        uv[ 5 ] = ty;
        uv[ 6 ] = rx;
        uv[ 7 ] = by;

        this->width = width;
        this->height = height;
}


void RectangularRegion::getDimensions( size_t* width, size_t* height )
{
        *width = this->width;
        *height = this->height;
}


const float* RectangularRegion::getUVCoordinates()
{
        return uv;
}
