#include <ege/opengl/shader.hxx>
#include <GL/glew.h>
#include <ege/exception.hxx>

namespace ege
{
    namespace opengl
    {
        Shader::Shader(ShaderType type, const std::string& code):
            Object(glCreateShader((GLenum) type))
        {
            const GLchar* codePtr = code.c_str();
            glShaderSource(id, 1, &codePtr, NULL);
            glCompileShader(id);
            GLint status;
            glGetShaderiv(id, GL_COMPILE_STATUS, &status);

            if (status != GL_TRUE)
            {
                GLint len;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
                char log[len];
                glGetShaderInfoLog(id, len, NULL, log);
                glDeleteShader(id);
                exception::throwNew("can't compile OpenGL shader:\n%s", log);
            }
        }

        Shader::~Shader()
        {
            glDeleteShader(id);
        }
    }
}
