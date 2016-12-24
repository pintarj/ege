#include <ege/graphic/gpu/buffer.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>


using namespace ege;
using namespace ege::graphic::gpu;


static inline unsigned int generateBuffer()
{
        unsigned int id;
        glGenBuffers( 1, &id );
        return id;
}


static inline unsigned int calculateUsageFlag( buffer::usage::Frequency frequency, buffer::usage::Nature nature )
{
        switch ( frequency )
        {
                case buffer::usage::Frequency::STREAM:
                        switch ( nature )
                        {
                                case buffer::usage::Nature::DRAW:
                                        return GL_STREAM_DRAW;

                                case buffer::usage::Nature::READ:
                                        return GL_STREAM_READ;

                                case buffer::usage::Nature::COPY:
                                        return GL_STREAM_COPY;
                        }

                case buffer::usage::Frequency::STATIC:
                        switch ( nature )
                        {
                                case buffer::usage::Nature::DRAW:
                                        return GL_DYNAMIC_DRAW;

                                case buffer::usage::Nature::READ:
                                        return GL_DYNAMIC_READ;

                                case buffer::usage::Nature::COPY:
                                        return GL_DYNAMIC_COPY;
                        }

                case buffer::usage::Frequency::DYNAMIC:
                        switch ( nature )
                        {
                                case buffer::usage::Nature::DRAW:
                                        return GL_DYNAMIC_DRAW;

                                case buffer::usage::Nature::READ:
                                        return GL_DYNAMIC_READ;

                                case buffer::usage::Nature::COPY:
                                        return GL_DYNAMIC_COPY;
                        }
        }
}


buffer::map::Range::Range( Buffer &buffer, unsigned int offset, unsigned int length, unsigned int access ):
        buffer( buffer ), offset( offset ), length( length ), access( access )
{
        if ( buffer.mappedRange != nullptr )
                ege::exception::throwNew( "can't map gpu buffer, because it's already mapped" );

        buffer.mappedRange = this;
        glBindBuffer( GL_COPY_WRITE_BUFFER, buffer.id );
}


buffer::map::Range::~Range()
{
        glBindBuffer( GL_COPY_WRITE_BUFFER, buffer.id );
        glUnmapBuffer( GL_COPY_WRITE_BUFFER );
        buffer.mappedRange = nullptr;
}


buffer::map::WriteRange::WriteRange( Buffer &buffer, unsigned int offset, unsigned int length, unsigned int access ):
        Range( buffer, offset, length, access | GL_MAP_WRITE_BIT ),
        mappedMemory( glMapBufferRange( GL_COPY_WRITE_BUFFER, offset, length, this->access ) ),
        flushExplicit( ( access & GL_MAP_FLUSH_EXPLICIT_BIT ) != 0 )
{

}


void buffer::map::WriteRange::flush( unsigned int offset, unsigned int length ) const
{
        glBindBuffer( GL_COPY_WRITE_BUFFER, object::getId( buffer ) );
        glFlushMappedBufferRange( GL_COPY_WRITE_BUFFER, offset, length );
}


buffer::map::ReadRange::ReadRange( Buffer &buffer, unsigned int offset, unsigned int length, unsigned int access ):
        Range( buffer, offset, length, access | GL_MAP_READ_BIT ), mappedMemory( glMapBufferRange( GL_COPY_WRITE_BUFFER, offset, length, this->access ) )
{

}


Buffer::Buffer( unsigned int size, buffer::usage::Frequency frequency, buffer::usage::Nature nature, const void* data ): Object( generateBuffer() )
{
        this->mappedRange = nullptr;
        reallocate( size, frequency, nature, data );
}


Buffer::~Buffer()
{
        glDeleteBuffers( 1, &id );
}


void Buffer::reallocate( unsigned int size, buffer::usage::Frequency frequency, buffer::usage::Nature nature,
                         const void* data )
{
        this->size = size;
        this->usageFrequency = frequency;
        this->usageNature = nature;
        this->usageCacheFlag = calculateUsageFlag( frequency, nature );
        glBindBuffer( GL_COPY_WRITE_BUFFER, id );
        glBufferData( GL_COPY_WRITE_BUFFER, size, data, usageCacheFlag );
}


void Buffer::reallocate( unsigned int size, const void* data )
{
        this->size = size;
        glBindBuffer( GL_COPY_WRITE_BUFFER, id );
        glBufferData( GL_COPY_WRITE_BUFFER, size, data, usageCacheFlag );
}


void Buffer::invalidateData()
{
        glBindBuffer( GL_COPY_WRITE_BUFFER, id );
        glBufferData( GL_COPY_WRITE_BUFFER, size, nullptr, usageCacheFlag );
}


unsigned int Buffer::getSize() const
{
        return size;
}


bool Buffer::isMapped() const
{
        return mappedRange != nullptr;
}


buffer::map::Range& Buffer::getMappedRange() const
{
        return *mappedRange;
}
