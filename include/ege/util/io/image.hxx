

#ifndef EGE_UTIL_IO_IMAGE_HXX
#define EGE_UTIL_IO_IMAGE_HXX


#include <ege/graphic/gpu/util/image/buffer.hxx>


namespace ege
{
        namespace util
        {
                namespace io
                {
                        namespace image
                        {
                                graphic::gpu::util::image::Buffer* loadPng( const char* fileName );
                                graphic::gpu::util::image::Buffer* load( const char* fileName );
                        }
                }
        }
}


#endif
