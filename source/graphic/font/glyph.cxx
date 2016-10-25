#include <ege/graphic/font/glyph.hxx>


using namespace ege::graphic::font;


Glyph::Glyph( int offsetLeft, int offsetTop, float advanceX, gpu::texture::util::RectangularRegion* region, bool textureShouldBeDeleted ):
        offsetLeft( offsetLeft ), offsetTop( offsetTop ), advanceX( advanceX ), region( region ), textureShouldBeDeleted( textureShouldBeDeleted )
{

}


Glyph::~Glyph()
{
        if ( textureShouldBeDeleted )
                delete &region->texture;

        delete region;
}


const ege::graphic::gpu::texture::util::RectangularRegion& Glyph::getRegion()
{
        return *region;
}
