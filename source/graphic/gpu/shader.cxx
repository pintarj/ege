#include <ege/graphic/gpu/shader.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


Shader::Shader( shader::Type type, const char* sourceCode ): Object( glCreateShader( ( GLenum ) type ) )
{
        glShaderSource( id, 1, &sourceCode, NULL );
        glCompileShader( id );

        GLint status;
        glGetShaderiv( id, GL_COMPILE_STATUS, &status );

        if ( status != GL_TRUE )
        {
                GLint len;
                glGetShaderiv( id, GL_INFO_LOG_LENGTH, &len );

                char log[ len ];
                glGetShaderInfoLog( id, len, NULL, log );
                glDeleteShader( id );
                Exception::throwNew( "can not compile GL shader: %s", log );
        }
}


Shader::~Shader()
{
        glDeleteShader( id );
}
