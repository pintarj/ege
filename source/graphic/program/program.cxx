#include <ege/graphic/program/program.hxx>
#include <GL/glew.h>


using namespace ege::graphic::program;


static inline GLuint compileShader( GLenum type, const char* source, char** log = nullptr )
{
        GLuint id = glCreateShader( type );
        glShaderSource( id, 1, &source, NULL );
        glCompileShader( id );

        GLint status;
        glGetShaderiv( id, GL_COMPILE_STATUS, &status );

        if ( status != GL_TRUE && log != nullptr )
        {
                GLint len;
                glGetShaderiv( id, GL_INFO_LOG_LENGTH, &len );

                *log = new char[ len ];
                glGetShaderInfoLog( id, len, NULL, *log );

                glDeleteShader( id );
                return 0;
        }

        return id;
}


static inline GLuint linkProgram( size_t* shadersId, size_t shadersCount, char** log = nullptr )
{
        GLuint id = glCreateProgram();

        for ( size_t i = 0; i < shadersCount; ++i )
                glAttachShader( id, ( GLuint ) shadersId[ i ] );

        glLinkProgram( id );

        for ( size_t i = 0; i < shadersCount; ++i )
                glDetachShader( id, ( GLuint ) shadersId[ i ] );

        GLint status;
        glGetProgramiv( id, GL_LINK_STATUS, &status );

        if ( status != GL_TRUE && log != nullptr )
        {
                GLint len;
                glGetProgramiv( id, GL_INFO_LOG_LENGTH, &len );

                *log = new char[ len ];
                glGetProgramInfoLog( id, len, NULL, *log );

                glDeleteProgram( id );
                return 0;
        }

        return id;
}


static inline size_t compileProgramFromVertexAndFragmentShader( const char* vertexShader, const char* fragmentShader )
{
        size_t shaders[ 2 ];
        shaders[ 0 ] = compileShader( GL_VERTEX_SHADER, vertexShader );
        shaders[ 1 ] = compileShader( GL_FRAGMENT_SHADER, fragmentShader );
        GLuint program = linkProgram( shaders, 2 );
        return program;
}


Program::Program( size_t glProgramId ): glProgramId( glProgramId )
{

}


Program::Program( const char* vertexShader, const char* fragmentShader ): Program( compileProgramFromVertexAndFragmentShader( vertexShader, fragmentShader ) )
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