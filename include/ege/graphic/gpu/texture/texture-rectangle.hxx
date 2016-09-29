

#ifndef EGE_GRAPHIC_GPU_TEXTURE_TEXTURE_RECTANGLE_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_TEXTURE_RECTANGLE_HXX


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
                                class TextureRectangle: public TwoDimensionalTexture
                                {
                                        public:
                                                TextureRectangle( const util::ImageBuffer& imageBuffer, Format format );
                                                TextureRectangle( const util::ImageBuffer& imageBuffer );
                                                TextureRectangle( unsigned int width, unsigned int height, Format format = Format::RGBA );
                                                virtual ~TextureRectangle();
                                };
                        }
                }
        }
}


#endif
