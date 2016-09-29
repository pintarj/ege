

#ifndef EGE_GRAPHIC_GPU_TEXTURE_TWO_DIMENSIONAL_TEXTURE_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_TWO_DIMENSIONAL_TEXTURE_HXX


#include <ege/graphic/gpu/texture.hxx>
#include <ege/graphic/gpu/texture/util/image-buffer.hxx>
#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace texture
                        {
                                class TwoDimensionalTexture: public Texture
                                {
                                        private:
                                                unsigned int width;
                                                unsigned int height;

                                        protected:
                                                TwoDimensionalTexture( Type type, const util::ImageBuffer& imageBuffer, Format format );
                                                TwoDimensionalTexture( Type type, const util::ImageBuffer& imageBuffer );
                                                TwoDimensionalTexture( Type type, unsigned int width, unsigned int height, Format format );

                                        public:
                                                virtual ~TwoDimensionalTexture();
                                                unsigned int getWidth() const;
                                                unsigned int getHeight() const;
                                                void substitute( unsigned int x, unsigned int y, const util::ImageBuffer& imageBuffer );

                                                void resize( unsigned int width, unsigned int height, unsigned int sourceX, unsigned int sourceY,
                                                        unsigned int destinationX, unsigned int destinationY, unsigned int copyWidth, unsigned int copyHeight );

                                                void resize( unsigned int width, unsigned int height, bool keepData = true );
                                };
                        }
                }
        }
}


#endif
