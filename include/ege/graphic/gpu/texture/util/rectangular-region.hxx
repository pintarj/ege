

#ifndef EGE_GRAPHIC_GPU_TEXTURE_UTIL_RECTANGULAR_REGION_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_UTIL_RECTANGULAR_REGION_HXX


#include <ege/graphic/gpu/texture/two-dimensional-texture.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace texture
                        {
                                namespace util
                                {
                                        class RectangularRegion
                                        {
                                                private:
                                                        float uv[ 8 ];
                                                        const bool recalculationCouldMakeSense;

                                                        RectangularRegion( const TwoDimensionalTexture& texture, unsigned int x,
                                                                unsigned int y, unsigned int width, unsigned int height, bool recalculationCouldMakeSense );

                                                        void calculateUV();

                                                public:
                                                        const TwoDimensionalTexture& texture;
                                                        const unsigned int x;
                                                        const unsigned int y;
                                                        const unsigned int width;
                                                        const unsigned int height;

                                                        RectangularRegion( const TwoDimensionalTexture& texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                                                        RectangularRegion( const TwoDimensionalTexture& texture );
                                                        void recalculateUV();
                                                        const float* getUVCoordinates() const;
                                        };
                                }
                        }
                }
        }
}


#endif
