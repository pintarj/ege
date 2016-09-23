

#ifndef EGE_GRAPHIC_GPU_UTIL_BUFFER_STREAM_WRITE_MAPPER_HXX
#define EGE_GRAPHIC_GPU_UTIL_BUFFER_STREAM_WRITE_MAPPER_HXX


#include <ege/graphic/gpu/buffer.hxx>
#include <ege/graphic/gpu/util/buffer/write-mapper.hxx>


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
                                        class StreamWriteMapper: public WriteMapper< unit >
                                        {
                                                private:
                                                        size_t flushedUnits;
                                                        size_t nextIndex;

                                                        void prepareSector( size_t , size_t includeNPrevUnits = 0 );

                                                protected:
                                                        void performFlush();

                                                public:
                                                        StreamWriteMapper( gpu::Buffer* buffer, size_t unitsPerSector, size_t sectorsCount, size_t offset = 0 );
                                                        virtual ~StreamWriteMapper() {};
                                                        unit* mapNext();
                                                        unit* mapNext( size_t count );
                                                        void reset();

                                                        using WriteMapper< unit >::unmap;
                                        };
                                }
                        }
                }
        }
}


#include "stream-write-mapper.txx"


#endif
