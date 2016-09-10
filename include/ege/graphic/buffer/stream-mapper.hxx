

#ifndef EGE_GRAPHIC_BUFFER_STREAM_MAPPER_HXX
#define EGE_GRAPHIC_BUFFER_STREAM_MAPPER_HXX


#include <ege/graphic/buffer/mapper.hxx>


namespace ege
{
        namespace graphic
        {
                namespace buffer
                {
                        template < typename unit >
                        class StreamMapper: public Mapper< unit >
                        {
                                private:
                                        size_t flushed_units;
                                        size_t next_index;

                                        void prepareSector( size_t , size_t includeNPrevUnits = 0 );

                                protected:
                                        void performFlush();

                                public:
                                        StreamMapper( size_t sectorSize = 32768, size_t sectorsCount = 2 );
                                        virtual ~StreamMapper();
                                        unit* mapNext();
                                        unit* mapNext( size_t nUnits );
                                        void reset();
                        };
                }
        }
}


template < typename unit >
ege::graphic::buffer::StreamMapper< unit >::StreamMapper( size_t sectorSize, size_t sectorsCount ): Mapper< unit >( gpu::BufferUsage::STREAM, sectorSize, sectorsCount )
{
        prepareSector( 0 );
}


template < typename unit >
ege::graphic::buffer::StreamMapper< unit >::~StreamMapper()
{

}


template < typename unit >
void ege::graphic::buffer::StreamMapper< unit >::prepareSector( size_t index, size_t includeNPrevUnits )
{
        this->mapSector( index, { gpu::BufferMapAccess::INVALIDATE_RANGE, gpu::BufferMapAccess::UNSYNCHRONIZED, gpu::BufferMapAccess::FLUSH_EXPLICIT }, includeNPrevUnits );
        flushed_units = 0;
        next_index = 0;
}


template < typename unit >
void ege::graphic::buffer::StreamMapper< unit >::performFlush()
{
        this->buffer->flushRange( flushed_units * sizeof( unit ), ( next_index - flushed_units ) * sizeof( unit ) );
        flushed_units = next_index;
}


template < typename unit >
unit* ege::graphic::buffer::StreamMapper< unit >::mapNext()
{
        if ( next_index == this->unitsPerSector )
        {
                if ( this->mappedSector + 1 == this->sectorsCount )
                        return nullptr;
                else
                        prepareSector( this->mappedSector + 1 );
        }

        return &this->mappedArea[ next_index++ ];
}


template < typename unit >
unit* ege::graphic::buffer::StreamMapper< unit >::mapNext( size_t nUnits )
{
        if ( ( next_index + nUnits - 1 ) >= this->unitsPerSector )
        {
                if ( this->mappedSector + 1 == this->sectorsCount )
                        return nullptr;
                else
                        prepareSector( this->mappedSector + 1, this->unitsPerSector - next_index );
        }

        unit* mappedUnits = &this->mappedArea[ next_index ];
        next_index += nUnits;
        return mappedUnits;
}


template < typename unit >
void ege::graphic::buffer::StreamMapper< unit >::reset()
{
        this->unmap();
        this->buffer->orphan();
        prepareSector( 0 );
}


#endif
