#include <ege_private/opengl/shader.hxx>


using namespace ege_private::opengl;


static char* lastShaderCompileLog = nullptr;


static void clearLastShaderCompileLog()
{
        if ( lastShaderCompileLog != nullptr )
        {
                delete lastShaderCompileLog;
                lastShaderCompileLog = nullptr;
        }
}


GLuint shader::compile( GLenum type, const char* source )
{
        GLuint id = glCreateShader( type );
        glShaderSource( id, 1, &source, NULL );
        glCompileShader( id );

        GLint status;
        glGetShaderiv( id, GL_COMPILE_STATUS, &status );

        if ( status != GL_TRUE )
        {
                GLint len;
                glGetShaderiv( id, GL_INFO_LOG_LENGTH, &len );

                char* log = new char[ len ];
                glGetShaderInfoLog( id, len, NULL, log );
                clearLastShaderCompileLog();
                lastShaderCompileLog = log;
                return 0;
        }

        return id;
}


const char* shader::getLastCompileLog()
{
        return ( const char* ) lastShaderCompileLog;
}


void shader::system::clearCache()
{
        clearLastShaderCompileLog();
}