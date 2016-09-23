

#ifndef EGE_GRAPHIC_GPU_UTIL_TEXTURE_RECTANGULAR_REGION_HXX
#define EGE_GRAPHIC_GPU_UTIL_TEXTURE_RECTANGULAR_REGION_HXX


#include <ege/graphic/gpu/texture-2D.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace util
                        {
                                namespace texture
                                {
                                        class RectangularRegion
                                        {
                                                private:
                                                        unsigned int x;
                                                        unsigned int y;
                                                        float uv[ 8 ];

                                                        void calculateUV();

                                                public:
                                                        const gpu::Texture2D& texture;
                                                        const unsigned int width;
                                                        const unsigned int height;

                                                        RectangularRegion( const gpu::Texture2D& texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                                                        RectangularRegion( const gpu::Texture2D& texture );
                                                        const float* getUVCoordinates();
                                        };
                                }
                        }
                }
        }
}


#endif
