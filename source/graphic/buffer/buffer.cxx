#include <ege/graphic/buffer/buffer.hxx>
#include <GL/glew.h>


using namespace ege::graphic::buffer;


static inline GLenum toGlUsage( BufferUsage usage )
{
        switch ( usage )
        {
                case BufferUsage::STREAM:
                        return GL_STREAM_DRAW;

                case BufferUsage::STATIC:
                        return GL_STATIC_DRAW;

                case BufferUsage::DYNAMIC:
                        return GL_DYNAMIC_DRAW;
        }
}


Buffer::Buffer( size_t sizeInBytes, const void* data, BufferUsage usage )
{
        GLuint id;
        glGenBuffers( 1, &id );
        glBindBuffer( GL_ARRAY_BUFFER, id );
        glBufferData( GL_ARRAY_BUFFER, sizeInBytes, data, toGlUsage( usage ) );
        glBufferId = id;
        this->usage = usage;
        size = sizeInBytes;
}


Buffer::~Buffer()
{
        GLuint id = ( GLuint ) glBufferId;
        glDeleteBuffers( 1, &id );
}


size_t Buffer::getSize()
{
        return size;
}


size_t Buffer::getBufferId()
{
        return glBufferId;
}


void* Buffer::map( size_t offset, size_t length, std::initializer_list< BufferMapAccess > access )
{
        GLenum flags = GL_MAP_WRITE_BIT;

        for ( auto flag : access )
                flags |= ( GLenum ) flag;

        glBindBuffer( GL_ARRAY_BUFFER, ( GLuint ) glBufferId );
        return glMapBufferRange( GL_ARRAY_BUFFER, offset, length, flags );
}


void* Buffer::mapAll( std::initializer_list< BufferMapAccess > access )
{
        return map( 0, size, access );
}


void Buffer::unmap()
{
        glBindBuffer( GL_ARRAY_BUFFER, ( GLuint ) glBufferId );
        glUnmapBuffer( GL_ARRAY_BUFFER );
}


void Buffer::invalidateData()
{
        glBindBuffer( GL_ARRAY_BUFFER, ( GLuint ) glBufferId );
        glBufferData( GL_ARRAY_BUFFER, size, NULL, toGlUsage( usage ) );
}


void Buffer::orphan()
{
        invalidateData();
}


void Buffer::flushRange( size_t offset, size_t length )
{
        glBindBuffer( GL_ARRAY_BUFFER, ( GLuint ) glBufferId );
        glFlushMappedBufferRange( GL_ARRAY_BUFFER, offset, length );
}
