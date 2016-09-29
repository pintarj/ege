

template < typename unit >
ege::graphic::gpu::buffer::util::WriteMapper< unit >::WriteMapper( gpu::Buffer* buffer, size_t unitsPerSector, size_t sectorsCount, size_t offset ):
        Mapper< unit >( buffer, unitsPerSector, sectorsCount, offset )
{

}


template < typename unit >
void ege::graphic::gpu::buffer::util::WriteMapper< unit >::mapSector( size_t index, std::initializer_list <gpu::buffer::map::WriteAccess> access, size_t includeNPrevUnits )
{
        unmap();
        size_t prevUnitsInBytes = includeNPrevUnits * sizeof( unit );
        range = new ege::graphic::gpu::buffer::map::WriteRange( *this->buffer, this->offset + index * this->sectorSize - prevUnitsInBytes, this->sectorSize + prevUnitsInBytes, access );
        mappedArea = ( unit* ) range->mappedMemory;
        mappedSectorIndex = index;
}


template < typename unit >
const ege::graphic::gpu::buffer::map::WriteRange& ege::graphic::gpu::buffer::util::WriteMapper< unit >::getRange()
{
        return *range;
}


template < typename unit >
unit* ege::graphic::gpu::buffer::util::WriteMapper< unit >::getMappedArea()
{
        return this->mappedArea;
}


template < typename unit >
size_t ege::graphic::gpu::buffer::util::WriteMapper< unit >::getMappedSectorIndex()
{

}


template < typename unit >
void ege::graphic::gpu::buffer::util::WriteMapper< unit >::unmap()
{
        if ( range != nullptr )
        {
                if ( range->flushExplicit )
                        performFlush();

                delete range;
                range = nullptr;
        }
}


template < typename unit >
void ege::graphic::gpu::buffer::util::WriteMapper< unit >::flush()
{
        if ( range == nullptr )
                return;

        performFlush();
}
