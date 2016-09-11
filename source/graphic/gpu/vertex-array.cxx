#include <ege/graphic/gpu/vertex-array.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


static inline unsigned int createVertexArray()
{
        unsigned int id;
        glCreateVertexArrays( 1, &id );
        return id;
}


VertexArray::VertexArray(): Object( createVertexArray() )
{

}


VertexArray::~VertexArray()
{
        glDeleteVertexArrays( 1, &id );
}


void VertexArray::enableAttribute( unsigned int index )
{
        glBindVertexArray( id );
        glEnableVertexAttribArray( index );
}


void VertexArray::disableAttribute( unsigned int index )
{
        glBindVertexArray( id );
        glDisableVertexAttribArray( index );
}


void VertexArray::setAttributeFormatAndBindVertexBuffer(  unsigned int index, uint8_t size, vertexArray::attribute::Type type,
                                                          bool normalized, const gpu::Buffer& buffer, unsigned int offset, unsigned int stride  )
{
        glBindVertexArray( id );
        glBindBuffer( GL_ARRAY_BUFFER, buffer.id );
        glVertexAttribPointer( index, size, ( GLenum ) type, ( GLboolean ) ( normalized ? GL_TRUE : GL_FALSE ), stride, reinterpret_cast< const void* >( ( size_t ) offset ) );
}


void VertexArray::bind() const
{
        glBindVertexArray( id );
}
