

#ifndef EGE_GRAPHIC_FONT_GLYPH_HXX
#define EGE_GRAPHIC_FONT_GLYPH_HXX


#include <ege/graphic/gpu/texture/util/rectangular-region.hxx>


namespace ege
{
        namespace graphic
        {
                namespace font
                {
                        class Glyph
                        {
                                protected:
                                        const gpu::texture::util::RectangularRegion* region;

                                        Glyph( int offsetLeft, int offsetTop, float advanceX, const gpu::texture::util::RectangularRegion* region );

                                public:
                                        const int offsetLeft;
                                        const int offsetTop;
                                        const float advanceX;

                                        virtual ~Glyph() {};
                                        const gpu::texture::util::RectangularRegion& getRegion();
                        };
                }
        }
}


#endif
