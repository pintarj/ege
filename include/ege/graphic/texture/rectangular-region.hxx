

#ifndef EGE_GRAPHIC_TEXTURE_RECTANGULAR_REGION_HXX
#define EGE_GRAPHIC_TEXTURE_RECTANGULAR_REGION_HXX


#include <ege/graphic/texture/region.hxx>
#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace texture
                {
                        class RectangularRegion: public Region
                        {
                                protected:
                                        size_t x;
                                        size_t y;
                                        size_t width;
                                        size_t height;
                                        float uv[ 8 ];

                                        void calculateUV();

                                public:
                                        RectangularRegion( gpu::Texture2D& texture );
                                        RectangularRegion( gpu::Texture2D& texture, size_t x, size_t y, size_t width, size_t height );
                                        void getDimensions( size_t* width, size_t* height );
                                        const float* getUVCoordinates();
                        };
                }
        }
}


#endif
