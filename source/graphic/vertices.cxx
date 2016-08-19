#include <ege/graphic/vertices.hxx>
#include <GL/glew.h>


using namespace ege::graphic;


Vertices::Vertices()
{
        pointer = nullptr;
        count = 0;
        glBuffer = 0;
}


Vertices::~Vertices()
{
        deallocate();
}


void Vertices::allocate( size_t count )
{
        deallocate();
        this->count = count;
        glGenBuffers( 1, &glBuffer );
        glBindBuffer( GL_ARRAY_BUFFER, glBuffer );
        glBufferData( GL_ARRAY_BUFFER, count * sizeof( float ), NULL, GL_DYNAMIC_DRAW );
}


void Vertices::deallocate()
{
        if ( glBuffer != 0 )
        {
                glDeleteBuffers( 1, &glBuffer );
                glBuffer = 0;
        }
}


float* Vertices::map( size_t offset, size_t count )
{
        unmap();
        glBindBuffer( GL_ARRAY_BUFFER, glBuffer );
        pointer = ( float* ) glMapBufferRange( GL_ARRAY_BUFFER, offset, count, GL_MAP_WRITE_BIT );
        return pointer;
}


float* Vertices::mapAll()
{
        return map( 0, count );
}


void Vertices::unmap()
{
        if ( pointer != nullptr )
        {
                glBindBuffer( GL_ARRAY_BUFFER, glBuffer );
                glUnmapBuffer( GL_ARRAY_BUFFER );
                pointer = nullptr;
        }
}


unsigned int Vertices::getId()
{
        return glBuffer;
}
