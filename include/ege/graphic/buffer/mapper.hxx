

#ifndef EGE_GRAPHIC_BUFFER_MAPPER_HXX
#define EGE_GRAPHIC_BUFFER_MAPPER_HXX


#include <ege/graphic/gpu/buffer.hxx>
#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace buffer
                {
                        template < typename unit >
                        class Mapper
                        {
                                protected:
                                        size_t sectorSize;
                                        size_t sectorsCount;
                                        size_t unitsPerSector;
                                        size_t unitsCount;
                                        gpu::Buffer* buffer;
                                        gpu::buffer::map::WriteRange* range;
                                        unit* mappedArea;
                                        size_t mappedSector;

                                        Mapper( gpu::buffer::usage::Frequency usage, size_t sectorSize, size_t sectorsCount );
                                        void mapSector( size_t sector, std::initializer_list< gpu::buffer::map::WriteAccess > access, size_t includeNPrevUnits = 0 );
                                        void unmap();
                                        virtual void performFlush() = 0;

                                public:
                                        virtual ~Mapper();
                                        gpu::Buffer* getBuffer();
                                        size_t getUnitsCount();
                                        void flush();
                        };
                }
        }
}


template < typename unit >
ege::graphic::buffer::Mapper< unit >::Mapper( gpu::buffer::usage::Frequency usage, size_t sectorSize, size_t sectorsCount )
{
        const size_t excess = ( sectorSize % sizeof( unit ) );

        if ( excess != 0 )
                sectorSize = sectorSize - excess + sizeof( unit );

        const size_t bufferSize = sectorSize * sectorsCount;
        this->buffer = new gpu::Buffer( bufferSize, usage, gpu::buffer::usage::Nature::DRAW );
        this->range = nullptr;
        this->mappedArea = nullptr;
        this->sectorSize = sectorSize;
        this->sectorsCount = sectorsCount;
        this->unitsPerSector = sectorSize / sizeof( unit );
        this->unitsCount = bufferSize / sizeof( unit );
}


template < typename unit >
ege::graphic::buffer::Mapper< unit >::~Mapper()
{
        if ( range != nullptr )
                delete range;

        delete buffer;
}


template < typename unit >
void ege::graphic::buffer::Mapper< unit >::mapSector( size_t sector, std::initializer_list< gpu::buffer::map::WriteAccess > access, size_t includeNPrevUnits )
{
        if ( range != nullptr )
        {
                performFlush();
                delete range;
        }

        size_t prevUnitsInBytes = includeNPrevUnits * sizeof( unit );
        range = new gpu::buffer::map::WriteRange( *buffer, sector * sectorSize - prevUnitsInBytes, sectorSize + prevUnitsInBytes, access );
        mappedArea = ( unit* ) range->mappedMemory;
        mappedSector = sector;
}


template < typename unit >
void ege::graphic::buffer::Mapper< unit >::unmap()
{
        if ( range != nullptr )
        {
                delete range;
                range = nullptr;
        }

}


template < typename unit >
ege::graphic::gpu::Buffer* ege::graphic::buffer::Mapper< unit >::getBuffer()
{
        return buffer;
}


template < typename unit >
size_t ege::graphic::buffer::Mapper< unit >::getUnitsCount()
{
        return unitsCount;
}


template < typename unit >
void ege::graphic::buffer::Mapper< unit >::flush()
{
        if ( range == nullptr )
                return;

        performFlush();
}


#endif
