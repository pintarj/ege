#include <ege/graphic/gpu/vertex-array.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


VertexArray::VertexArray( vertexArray::Attribute* attributes, size_t count )
{
        GLuint id;
        glGenVertexArrays( 1, &id );
        glVertexArrayId = id;
        glBindVertexArray( id );

        for ( size_t i = 0; i < count; ++i )
        {
                vertexArray::Attribute& attribute = attributes[ i ];
                glEnableVertexAttribArray( ( GLuint ) attribute.vertexIndex );
                glBindBuffer( GL_ARRAY_BUFFER, ( GLuint ) attribute.buffer->getBufferId() );
                const void* offset = ( const void * ) attribute.offsetInBuffer;
                glVertexAttribPointer( ( GLuint ) attribute.vertexIndex, attribute.vectorSize, GL_FLOAT, GL_FALSE, ( GLsizei ) attribute.stride, offset );
        }
}


void VertexArray::use()
{
        glBindVertexArray( ( GLuint ) glVertexArrayId );
}


size_t VertexArray::getVertexArrayId()
{
        return  glVertexArrayId;
}


VertexArray::~VertexArray()
{
        GLuint id = ( GLuint ) glVertexArrayId;
        glDeleteVertexArrays( 1, &id );
}
