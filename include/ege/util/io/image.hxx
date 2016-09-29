

#ifndef EGE_UTIL_IO_IMAGE_HXX
#define EGE_UTIL_IO_IMAGE_HXX


#include <ege/graphic/gpu/texture/util/image-buffer.hxx>


namespace ege
{
        namespace util
        {
                namespace io
                {
                        namespace image
                        {
                                graphic::gpu::texture::util::ImageBuffer* loadPng( const char* fileName );
                                graphic::gpu::texture::util::ImageBuffer* load( const char* fileName );
                        }
                }
        }
}


#endif
