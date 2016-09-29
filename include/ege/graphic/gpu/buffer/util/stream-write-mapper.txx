

template < typename unit >
ege::graphic::gpu::buffer::util::StreamWriteMapper< unit >::StreamWriteMapper( gpu::Buffer* buffer, size_t unitsPerSector, size_t sectorsCount, size_t offset ):
        WriteMapper< unit >( buffer, unitsPerSector, sectorsCount, offset )
{
        prepareSector( 0 );
}


template < typename unit >
void ege::graphic::gpu::buffer::util::StreamWriteMapper< unit >::prepareSector( size_t index, size_t includeNPrevUnits )
{
        this->mapSector( index, { gpu::buffer::map::WriteAccess::INVALIDATE_RANGE, gpu::buffer::map::WriteAccess::UNSYNCHRONIZED, gpu::buffer::map::WriteAccess::FLUSH_EXPLICIT }, includeNPrevUnits );
        flushedUnits = 0;
        nextIndex = 0;
}


template < typename unit >
void ege::graphic::gpu::buffer::util::StreamWriteMapper< unit >::performFlush()
{
        if ( flushedUnits == nextIndex )
                return;

        this->getRange().flush( flushedUnits * sizeof( unit ), ( nextIndex - flushedUnits ) * sizeof( unit ) );
        flushedUnits = nextIndex;
}


template < typename unit >
unit* ege::graphic::gpu::buffer::util::StreamWriteMapper< unit >::mapNext()
{
        if ( nextIndex == this->unitsPerSector )
        {
                size_t mappedSectorIndex = this->getMappedSectorIndex();

                if ( mappedSectorIndex + 1 == this->sectorsCount )
                        return nullptr;
                else
                        prepareSector( mappedSectorIndex + 1 );
        }

        return &this->mappedArea[ nextIndex++ ];
}


template < typename unit >
unit* ege::graphic::gpu::buffer::util::StreamWriteMapper< unit >::mapNext( size_t nUnits )
{
        if ( ( nextIndex + nUnits - 1 ) >= this->unitsPerSector )
        {
                size_t mappedSectorIndex = this->getMappedSectorIndex();

                if ( mappedSectorIndex + 1 == this->sectorsCount )
                        return nullptr;
                else
                        prepareSector( mappedSectorIndex + 1, this->unitsPerSector - nextIndex );
        }

        unit* mappedUnits = &this->getMappedArea()[ nextIndex ];
        nextIndex += nUnits;
        return mappedUnits;
}


template < typename unit >
void ege::graphic::gpu::buffer::util::StreamWriteMapper< unit >::reset()
{
        prepareSector( 0 );
}
