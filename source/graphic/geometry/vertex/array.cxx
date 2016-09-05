#include <ege/graphic/geometry/vertex/array.hxx>
#include <GL/glew.h>


using namespace ege::graphic::geometry::vertex;


Array::Array( ArrayAttribute* attributes, size_t count )
{
        GLuint id;
        glGenVertexArrays( 1, &id );
        glBindVertexArray( id );

        for ( size_t i = 0; i < count; ++i )
        {
                ArrayAttribute& attribute = attributes[ i ];
                glEnableVertexAttribArray( ( GLuint ) attribute.vertexIndex );
                glBindBuffer( GL_ARRAY_BUFFER, ( GLuint ) attribute.buffer->getBufferId() );
                const void* offset = ( const void * ) attribute.offsetInBuffer;
                glVertexAttribPointer( ( GLuint ) attribute.vertexIndex, attribute.vectorSize, GL_FLOAT, GL_FALSE, ( GLsizei ) attribute.stride, offset );
        }
}


void Array::use()
{
        glBindVertexArray( ( GLuint ) glVertexArrayId );
}


size_t Array::getVertexArrayId()
{
        return  glVertexArrayId;
}
