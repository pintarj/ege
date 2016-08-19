#include <ege_private/opengl/program.hxx>


using namespace ege_private::opengl;


static char* lastProgramLinkLog = nullptr;


static void clearLastProgramLinkLog()
{
        if ( lastProgramLinkLog != nullptr )
        {
                delete lastProgramLinkLog;
                lastProgramLinkLog = nullptr;
        }
}


GLuint program::link( GLuint* shadersId, size_t shadersCount )
{
        GLuint id = glCreateProgram();

        for ( size_t i = 0; i < shadersCount; ++i )
                glAttachShader( id, shadersId[ i ] );

        glLinkProgram( id );

        for ( size_t i = 0; i < shadersCount; ++i )
                glDetachShader( id, shadersId[ i ] );

        GLint status;
        glGetProgramiv( id, GL_LINK_STATUS, &status );

        if ( status != GL_TRUE )
        {
                GLint len;
                glGetProgramiv( id, GL_INFO_LOG_LENGTH, &len );

                char* log = new char[ len ];
                glGetProgramInfoLog( id, len, NULL, log );

                clearLastProgramLinkLog();
                lastProgramLinkLog = log;
                glDeleteProgram( id );
                return 0;
        }

        return id;
}


const char* program::getLastLinkLog()
{
        return ( const char* ) lastProgramLinkLog;
}


void program::system::clearCache()
{
        clearLastProgramLinkLog();
}
