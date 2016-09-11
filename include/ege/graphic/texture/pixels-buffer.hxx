

#ifndef EGE_GRAPHIC_TEXTURE_PIXELS_BUFFER_HXX
#define EGE_GRAPHIC_TEXTURE_PIXELS_BUFFER_HXX


#include <ege/graphic/texture/format.hxx>
#include <ege/graphic/gpu/buffer.hxx>
#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace texture
                {
                        class PixelsBuffer
                        {
                                private:
                                        const size_t width;
                                        const size_t height;
                                        gpu::Buffer& pixels;
                                        const Format format;
                                        bool deleteBuffer;

                                public:
                                        PixelsBuffer( size_t width, size_t height, gpu::Buffer& pixels, Format format, bool deleteBuffer = false );
                                        PixelsBuffer( size_t width, size_t height, const void* pixels, Format format );
                                        virtual ~PixelsBuffer();
                                        void getDimensions( size_t* width, size_t* height );
                                        gpu::Buffer& getPixels();
                                        const Format getFormat();
                        };
                }
        }
}


#endif
