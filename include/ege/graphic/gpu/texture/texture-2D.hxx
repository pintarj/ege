

#ifndef EGE_GRAPHIC_GPU_TEXTURE_TEXTURE_2D_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_TEXTURE_2D_HXX


#include <ege/graphic/gpu/texture/two-dimensional-texture.hxx>
#include <ege/graphic/gpu/texture/util/image-buffer.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace texture
                        {
                                class Texture2D : public TwoDimensionalTexture
                                {
                                        public:
                                                Texture2D( const util::ImageBuffer& imageBuffer, Format format );
                                                Texture2D( const util::ImageBuffer& imageBuffer );
                                                Texture2D( unsigned int width, unsigned int height, Format format = Format::RGBA );
                                                virtual ~Texture2D();
                                };
                        }
                }
        }
}


#endif
