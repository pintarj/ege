#include <ege/exception.hxx>


template < typename unit >
ege::graphic::gpu::util::buffer::Mapper< unit >::Mapper( gpu::Buffer* buffer, size_t unitsPerSector, size_t sectorsCount, size_t offset ):
        buffer( buffer ), unitsPerSector( unitsPerSector ), sectorsCount( sectorsCount ), offset( offset ), sectorSize( unitsPerSector * sizeof( unit ) ), unitsCount( unitsPerSector * sectorsCount )
{

}
