

#ifndef EGE_GRAPHIC_GPU_UTIL_BUFFER_WRITE_MAPPER_HXX
#define EGE_GRAPHIC_GPU_UTIL_BUFFER_WRITE_MAPPER_HXX


#include <ege/graphic/gpu/buffer.hxx>
#include <ege/graphic/gpu/util/buffer/mapper.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace util
                        {
                                namespace buffer
                                {
                                        template < typename unit >
                                        class WriteMapper: public Mapper< unit >
                                        {
                                                private:
                                                        gpu::buffer::map::WriteRange* range;
                                                        unit* mappedArea;
                                                        size_t mappedSectorIndex;

                                                protected:
                                                        WriteMapper( gpu::Buffer* buffer, size_t unitsPerSector, size_t sectorsCount, size_t offset = 0 );
                                                        void mapSector( size_t index, std::initializer_list< gpu::buffer::map::WriteAccess > access, size_t includeNPrevUnits = 0 );
                                                        const gpu::buffer::map::WriteRange& getRange();
                                                        unit* getMappedArea();
                                                        size_t getMappedSectorIndex();
                                                        void unmap();
                                                        virtual void performFlush() = 0;

                                                public:
                                                        virtual ~WriteMapper() {};
                                                        void flush();
                                        };
                                }
                        }
                }
        }
}


#include "write-mapper.txx"


#endif
