#include <ege/graphic/gpu/program.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>
#include <cstring>


using namespace ege;
using namespace ege::graphic::gpu;


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


#define BUILD_ERROR_MESSAGE( message, pieces ) \
        size_t length = 0; \
        size_t count = sizeof( pieces ) / sizeof( char* ); \
        size_t lengths[ count ]; \
        for( size_t i = 0; i < count; ++i ) \
        { \
                lengths[ i ] = std::strlen( pieces[ i ] ); \
                length += lengths[ i ]; \
         } \
        char message[ length + 1 ]; \
        message[ length ] = '\0'; \
        char* destination = message; \
        for( size_t i = 0; i < count; ++i ) \
        { \
                std::memcpy( destination, pieces[ i ], lengths[ i ] ); \
                destination += lengths[ i ]; \
        } \


static inline size_t compileProgramFromVertexAndFragmentShader( const char* vertexShader, const char* fragmentShader )
{
        static const char* piecesShader[ 4 ] = { "could not compile ", "", " shader: \n", "" };
        static const char* piecesProgram[ 2 ] = { "could not link program: \n", "" };
        size_t shaders[ 2 ];
        char* log;

        shaders[ 0 ] = compileShader( GL_VERTEX_SHADER, vertexShader, &log );

        if ( shaders[ 0 ] == 0 )
        {
                piecesShader[ 1 ] = "vertex";
                piecesShader[ 3 ] = log;
                BUILD_ERROR_MESSAGE( message, piecesShader )
                delete log;
                exception::throwNew( message );
        }

        shaders[ 1 ] = compileShader( GL_FRAGMENT_SHADER, fragmentShader, &log );

        if ( shaders[ 1 ] == 0 )
        {
                piecesShader[ 1 ] = "fragment";
                piecesShader[ 3 ] = log;
                BUILD_ERROR_MESSAGE( message, piecesShader )
                glDeleteShader( ( GLuint ) shaders[ 0 ] );
                delete log;
                exception::throwNew( message );
        }

        GLuint program = linkProgram( shaders, 2, &log );
        glDeleteShader( ( GLuint ) shaders[ 0 ] );
        glDeleteShader( ( GLuint ) shaders[ 1 ] );

        if ( program == 0 )
        {
                piecesProgram[ 1 ] = log;
                BUILD_ERROR_MESSAGE( message, piecesProgram )
                delete log;
                exception::throwNew( message );
        }

        return program;
}


Program::Program( size_t glProgramId, bool deleteGlProgram ): glProgramId( glProgramId ), deleteGlProgram( deleteGlProgram )
{

}


Program::Program( const char* vertexShader, const char* fragmentShader ): Program( compileProgramFromVertexAndFragmentShader( vertexShader, fragmentShader ), true )
{

}


Program::~Program()
{
        if ( deleteGlProgram )
                glDeleteProgram( ( GLuint ) glProgramId );
}


void Program::use()
{
        glUseProgram( ( GLuint ) glProgramId );
}


const size_t Program::getProgramId()
{
        return glProgramId;
}