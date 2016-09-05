#include <ege/graphic/program/extension/model-view-projection-matrix.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>


using namespace ege;
using namespace ege::graphic::program::extension;


ModelViewProjectionMatrix::ModelViewProjectionMatrix( Program &program, const char* mvpMatrixName ): Extension( program )
{
        GLint location = glGetUniformLocation( ( GLuint ) program.getProgramId(), mvpMatrixName );

        if ( location == -1 )
                exception::throwNew( "could not find an uniform location", false );

        matrixLocation = ( size_t ) location;
}


void ModelViewProjectionMatrix::uniformMatrix( const float* matrix )
{
        glProgramUniformMatrix4fv( ( GLuint ) program.getProgramId(), ( GLint ) matrixLocation, 1, GL_FALSE, matrix );
}
