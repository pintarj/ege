

#ifndef EGE_GRAPHIC_GPU_TEXTURE_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_HXX


#include <ege/graphic/gpu/object.hxx>
#include <ege/graphic/gpu/texture/type.hxx>
#include <cstdint>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace texture
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

                        class Texture: public Object
                        {
                                protected:
                                        const texture::Format format;
                                        Texture( texture::Type type, texture::Format format );

                                public:
                                        const texture::Type type;

                                        virtual ~Texture();
                                        void bindAtUnit( unsigned int index ) const;
                        };
                }
        }
}


#endif
