

#ifndef EGE_UTIL_IO_IMAGE_HXX
#define EGE_UTIL_IO_IMAGE_HXX


#include <ege/graphic/texture/pixels-buffer.hxx>


namespace ege
{
        namespace util
        {
                namespace io
                {
                        namespace image
                        {
                                graphic::texture::PixelsBuffer* loadPng( const char* fileName );
                                graphic::texture::PixelsBuffer* load( const char* fileName );
                        }
                }
        }
}


#endif
