

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

                                        void prepareSector( size_t index );

                                protected:
                                        void performFlush();

                                public:
                                        StreamMapper( size_t sectorSize = 32768, size_t sectorsCount = 2 );
                                        virtual ~StreamMapper();
                                        unit* mapNext();
                                        void reset();
                        };
                }
        }
}


template < typename unit >
ege::graphic::buffer::StreamMapper< unit >::StreamMapper( size_t sectorSize, size_t sectorsCount ): Mapper< unit >( BufferUsage::STREAM, sectorSize, sectorsCount )
{
        prepareSector( 0 );
}


template < typename unit >
ege::graphic::buffer::StreamMapper< unit >::~StreamMapper()
{

}


template < typename unit >
void ege::graphic::buffer::StreamMapper< unit >::prepareSector( size_t index )
{
        this->mapSector( index, { BufferMapAccess::INVALIDATE_RANGE, BufferMapAccess::UNSYNCHRONIZED, BufferMapAccess::FLUSH_EXPLICIT } );
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
void ege::graphic::buffer::StreamMapper< unit >::reset()
{
        this->unmap();
        this->buffer->orphan();
        prepareSector( 0 );
}


#endif
