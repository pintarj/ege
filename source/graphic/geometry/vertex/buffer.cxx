#include <ege/graphic/geometry/vertex/buffer.hxx>
#include <GL/glew.h>


using namespace ege::graphic::geometry::vertex;


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
