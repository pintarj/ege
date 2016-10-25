

#ifndef EGE_GRAPHIC_FONT_GLYPH_HXX
#define EGE_GRAPHIC_FONT_GLYPH_HXX


#include <ege/graphic/font/face.hxx>
#include <ege/graphic/gpu/texture/util/rectangular-region.hxx>


namespace ege
{
        namespace graphic
        {
                namespace font
                {
                        class Face;

                        class Glyph
                        {
                                friend Face;

                                private:
                                        gpu::texture::util::RectangularRegion* region;
                                        bool textureShouldBeDeleted;

                                        Glyph( int offsetLeft, int offsetTop, float advanceX, gpu::texture::util::RectangularRegion* region, bool textureShouldBeDeleted );

                                public:
                                        const int offsetLeft;
                                        const int offsetTop;
                                        const float advanceX;

                                        virtual ~Glyph();
                                        const gpu::texture::util::RectangularRegion& getRegion();
                        };
                }
        }
}


#endif
