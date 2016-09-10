#include <ege/graphic/program/extension/textures.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>


using namespace ege;
using namespace ege::graphic::program::extension;


Textures::Textures( gpu::Program& program, const char** textureNames, size_t count ): Extension( program )
{
        texturesLocation = new size_t[ count ];

        for ( size_t i = 0; i < count; ++i )
        {
                GLint location = glGetUniformLocation( ( GLuint ) program.getProgramId(), textureNames[ i ] );

                if ( location == -1 )
                        exception::throwNew( "could not find an uniform location", false );

                texturesLocation[ i ] = ( size_t ) location;
        }
}


Textures::~Textures()
{
        delete texturesLocation;
}


void Textures::uniformTextureAt( size_t index, size_t value )
{
        glProgramUniform1i( ( GLuint ) program.getProgramId(), ( GLint ) texturesLocation[ index ], ( GLint ) value );
}
