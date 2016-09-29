

#ifndef EGE_GRAPHIC_GPU_BUFFER_UTIL_MAPPER_HXX
#define EGE_GRAPHIC_GPU_BUFFER_UTIL_MAPPER_HXX


#include <ege/graphic/gpu/buffer.hxx>
#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace buffer
                        {
                                namespace util
                                {
                                        template < typename unit >
                                        class Mapper
                                        {
                                                protected:
                                                        gpu::Buffer* const buffer;

                                                        Mapper( gpu::Buffer* buffer, size_t unitsPerSector, size_t sectorsCount, size_t offset = 0 );

                                                public:
                                                        const size_t unitsPerSector;
                                                        const size_t sectorsCount;
                                                        const size_t offset;
                                                        const size_t sectorSize;
                                                        const size_t unitsCount;

                                                        virtual ~Mapper() {};
                                        };
                                }
                        }
                }
        }
}


#include "mapper.txx"


#endif
