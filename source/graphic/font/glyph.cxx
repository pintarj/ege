#include <ege/graphic/font/glyph.hxx>


using namespace ege::graphic::font;


Glyph::Glyph( int offsetLeft, int offsetTop, float advanceX, const gpu::texture::util::RectangularRegion* region ):
        offsetLeft( offsetLeft ), offsetTop( offsetTop ), advanceX( advanceX ), region( region )
{

}


const ege::graphic::gpu::texture::util::RectangularRegion& Glyph::getRegion()
{
        return *region;
}
