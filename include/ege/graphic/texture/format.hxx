

#ifndef EGE_GRAPHIC_TEXTURE_FORMAT_HXX
#define EGE_GRAPHIC_TEXTURE_FORMAT_HXX


#include <cstdint>


namespace ege
{
        namespace graphic
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

                                constexpr uint16_t bytesPerPixel( Format format )
                                {
                                        switch ( format )
                                        {
                                                case Format::RGB:
                                                        return 3;

                                                case Format::RGBA:
                                                        return 4;
                                        }
                                }
                        }
                }
        }
}


#endif
