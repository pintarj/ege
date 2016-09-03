#include <ege/graphic/program/program.hxx>
#include <GL/glew.h>


using namespace ege::graphic::program;


Program::Program( size_t glProgramId ): glProgramId( glProgramId )
{

}


Program::~Program()
{

}


void Program::use()
{
        glUseProgram( ( GLuint ) glProgramId );
}


const size_t Program::getProgramId()
{
        return glProgramId;
}