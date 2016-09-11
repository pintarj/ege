

#ifndef EGE_GRAPHIC_GPU_UTIL_IMAGE_BUFFER_HXX
#define EGE_GRAPHIC_GPU_UTIL_IMAGE_BUFFER_HXX


#include <ege/graphic/gpu/buffer.hxx>
#include <memory>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace util
                        {
                                namespace image
                                {
                                        namespace buffer
                                        {
                                                enum class Format
                                                {
                                                        RGB = 0x1907,
                                                        RGBA = 0x1908
                                                };

                                                namespace format
                                                {
                                                        constexpr uint8_t bytesPerPixel( Format format )
                                                        {
                                                                switch ( format )
                                                                {
                                                                        case Format::RGB:
                                                                                return 3;

                                                                        case Format::RGBA:
                                                                                return 4;
                                                                }
                                                        }


                                                        constexpr bool hasAlpha( Format format )
                                                        {
                                                                switch ( format )
                                                                {
                                                                        case Format::RGB:
                                                                                return false;

                                                                        case Format::RGBA:
                                                                                return true;
                                                                }
                                                        }
                                                }
                                        }

                                        class Buffer
                                        {
                                                private:
                                                        std::shared_ptr< ege::graphic::gpu::Buffer > buffer;
                                                        unsigned int offset;

                                                public:
                                                        const unsigned int width;
                                                        const unsigned int height;
                                                        const buffer::Format format;

                                                        Buffer( unsigned int width, unsigned int height, buffer::Format format,
                                                                std::shared_ptr< ege::graphic::gpu::Buffer > buffer, unsigned int offset = 0 );

                                                        virtual ~Buffer();
                                                        const ege::graphic::gpu::Buffer& getBuffer() const;
                                                        unsigned int getInBufferOffset() const;
                                        };
                                }
                        }
                }
        }
}


#endif
