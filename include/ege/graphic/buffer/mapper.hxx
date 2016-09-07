

#ifndef EGE_GRAPHIC_BUFFER_MAPPER_HXX
#define EGE_GRAPHIC_BUFFER_MAPPER_HXX


#include <ege/graphic/buffer/buffer.hxx>
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
                                        Buffer* buffer;
                                        unit* mappedArea;
                                        size_t mappedSector;

                                        Mapper( BufferUsage usage, size_t sectorSize, size_t sectorsCount );
                                        void mapSector( size_t sector, std::initializer_list< BufferMapAccess > access );
                                        void unmap();
                                        virtual void performFlush() = 0;

                                public:
                                        virtual ~Mapper();
                                        Buffer* getBuffer();
                                        size_t getUnitsCount();
                                        void flush();
                        };
                }
        }
}


template < typename unit >
ege::graphic::buffer::Mapper< unit >::Mapper( BufferUsage usage, size_t sectorSize, size_t sectorsCount )
{
        const size_t excess = ( sectorSize % sizeof( unit ) );

        if ( excess != 0 )
                sectorSize = sectorSize - excess + sizeof( unit );

        const size_t bufferSize = sectorSize * sectorsCount;
        this->buffer = new Buffer( bufferSize, NULL, usage );
        this->mappedArea = nullptr;
        this->sectorSize = sectorSize;
        this->sectorsCount = sectorsCount;
        this->unitsPerSector = sectorSize / sizeof( unit );
        this->unitsCount = bufferSize / sizeof( unit );
}


template < typename unit >
ege::graphic::buffer::Mapper< unit >::~Mapper()
{
        delete buffer;
}


template < typename unit >
void ege::graphic::buffer::Mapper< unit >::mapSector( size_t sector, std::initializer_list< BufferMapAccess > access )
{
        if ( mappedArea != nullptr )
        {
                performFlush();
                buffer->unmap();
        }

        mappedArea = ( unit* ) buffer->map( sector * sectorSize, sectorSize, access );
        mappedSector = sector;
}


template < typename unit >
void ege::graphic::buffer::Mapper< unit >::unmap()
{
        buffer->unmap();
        mappedArea = nullptr;
}


template < typename unit >
ege::graphic::buffer::Buffer* ege::graphic::buffer::Mapper< unit >::getBuffer()
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
        if ( mappedArea == nullptr )
                return;

        performFlush();
}


#endif
