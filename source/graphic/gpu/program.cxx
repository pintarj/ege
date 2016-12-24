#include <ege/graphic/gpu/program.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>


using namespace ege;
using namespace ege::graphic::gpu;


Program::Program( std::initializer_list< const Shader* > shaders ): Object( glCreateProgram() )
{
        for ( const Shader* shader : shaders )
                glAttachShader( id, object::getId( *shader ) );

        glLinkProgram( id );

        for ( const Shader* shader : shaders )
                glDetachShader( id, object::getId( *shader ) );

        GLint status;
        glGetProgramiv( id, GL_LINK_STATUS, &status );

        if ( status != GL_TRUE )
        {
                GLint len;
                glGetProgramiv( id, GL_INFO_LOG_LENGTH, &len );

                char log[ len ];
                glGetProgramInfoLog( id, len, NULL, log );
                glDeleteProgram( id );
                ege::exception::throwNew( "can not link program: %d", log );
        }
}


Program::~Program()
{
        glDeleteProgram( id );
}


void Program::use() const
{
        glUseProgram( id );
}


int Program::getUniformLocation( const char* uniformName ) const
{
        return glGetUniformLocation( id, uniformName );
}


void Program::uniform( unsigned int location, int v0 )
{
        glProgramUniform1i( id, location, v0 );
}


void Program::uniformMatrix4x4( unsigned int location, unsigned int count, bool transpose, const float* matrix4x4 )
{
        glProgramUniformMatrix4fv( id, location, count, ( GLboolean ) ( transpose ? GL_TRUE : GL_FALSE ), matrix4x4 );
}
