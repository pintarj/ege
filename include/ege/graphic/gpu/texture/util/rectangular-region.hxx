

#ifndef EGE_GRAPHIC_GPU_TEXTURE_UTIL_RECTANGULAR_REGION_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_UTIL_RECTANGULAR_REGION_HXX


#include <ege/graphic/gpu/texture/texture-2D.hxx>


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

                                                public:
                                                        const Texture2D& texture;
                                                        const unsigned int x;
                                                        const unsigned int y;
                                                        const unsigned int width;
                                                        const unsigned int height;

                                                        RectangularRegion( const Texture2D& texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                                                        RectangularRegion( const Texture2D& texture );
                                                        void recalculateUV();
                                                        const float* getUVCoordinates() const;
                                        };
                                }
                        }
                }
        }
}


#endif
