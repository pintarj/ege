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


void Vertices::allocate( size_t count, uint8_t vectorDimension )
{
        deallocate();
        this->count = count;
        this->vectorDimension = vectorDimension;
        glGenBuffers( 1, &glBuffer );
        glBindBuffer( GL_ARRAY_BUFFER, glBuffer );
        glBufferData( GL_ARRAY_BUFFER, count * vectorDimension * sizeof( float ), NULL, GL_DYNAMIC_DRAW );
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
        const size_t factor = vectorDimension * sizeof( float );
        pointer = ( float* ) glMapBufferRange( GL_ARRAY_BUFFER, factor * offset, factor * count, GL_MAP_WRITE_BIT );
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


uint8_t Vertices::getDimension()
{
        return vectorDimension;
}


size_t Vertices::getCount()
{
        return count;
}


unsigned int Vertices::getId()
{
        return glBuffer;
}
