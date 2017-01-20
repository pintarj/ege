#include <ege/opengl/program.hxx>
#include <GL/glew.h>
#include <ege/exception.hxx>

namespace ege
{
    namespace opengl
    {
        ProgramConfiguration::ProgramConfiguration():
            shaders(),
            binaryRetrievableHint(false),
            separable(false)
        {

        }

        Program::Program(const ProgramConfiguration& conf):
            Object(glCreateProgram())
        {
            for (const Shader* shader : conf.shaders)
                glAttachShader(id, shader->id);

            glProgramParameteri(id, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, conf.binaryRetrievableHint ? GL_TRUE : GL_FALSE);
            glProgramParameteri(id, GL_PROGRAM_SEPARABLE, conf.separable ? GL_TRUE : GL_FALSE);
            glLinkProgram(id);

            for (const Shader* shader : conf.shaders)
                glDetachShader(id, shader->id);

            GLint status;
            glGetProgramiv(id, GL_LINK_STATUS, &status);

            if (status != GL_TRUE)
            {
                GLint len;
                glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
                char log[len];
                glGetProgramInfoLog(id, len, NULL, log);
                glDeleteProgram(id);
                exception::throwNew("can't link OpenGL program:\n%s", log);
            }
        }

        Program::Program(std::initializer_list<const Shader*> shaders):
            Program([shaders]() -> ProgramConfiguration
                {
                    ProgramConfiguration conf;
                    conf.shaders = shaders;
                    return conf;
                }())
        {

        }

        Program::~Program()
        {
            glDeleteProgram(id);
        }

        void Program::use() const
        {
            glUseProgram(id);
        }

        int Program::getUniformLocation(const std::string& name) const
        {
            return glGetUniformLocation(id, name.c_str());
        }

        void Program::uniform(int location, float f0)
        {
            glProgramUniform1f(id, location, f0);
        }

        void Program::uniform(int location, float f0, float f1)
        {
            glProgramUniform2f(id, location, f0, f1);
        }

        void Program::uniform(int location, float f0, float f1, float f2)
        {
            glProgramUniform3f(id, location, f0, f1, f2);
        }

        void Program::uniform(int location, float f0, float f1, float f2, float f3)
        {
            glProgramUniform4f(id, location, f0, f1, f2, f3);
        }

        void Program::uniform(int location, int i0)
        {
            glProgramUniform1i(id, location, i0);
        }

        void Program::uniform(int location, int i0, int i1)
        {
            glProgramUniform2i(id, location, i0, i1);
        }

        void Program::uniform(int location, int i0, int i1, int i2)
        {
            glProgramUniform3i(id, location, i0, i1, i2);
        }

        void Program::uniform(int location, int i0, int i1, int i2, int i3)
        {
            glProgramUniform4i(id, location, i0, i1, i2, i3);
        }

        void Program::uniform(int location, unsigned int ui0)
        {
            glProgramUniform1ui(id, location, ui0);
        }

        void Program::uniform(int location, unsigned int ui0, unsigned int ui1)
        {
            glProgramUniform2ui(id, location, ui0, ui1);
        }

        void Program::uniform(int location, unsigned int ui0, unsigned int ui1, unsigned int ui2)
        {
            glProgramUniform3ui(id, location, ui0, ui1, ui2);
        }

        void Program::uniform(int location, unsigned int ui0, unsigned int ui1, unsigned int ui2, unsigned int ui3)
        {
            glProgramUniform4ui(id, location, ui0, ui1, ui2, ui3);
        }

        void Program::uniformVector1(int location, int count, const float* value)
        {
            glProgramUniform1fv(id, location, count, value);
        }

        void Program::uniformVector2(int location, int count, const float* value)
        {
            glProgramUniform2fv(id, location, count, value);
        }

        void Program::uniformVector3(int location, int count, const float* value)
        {
            glProgramUniform3fv(id, location, count, value);
        }

        void Program::uniformVector4(int location, int count, const float* value)
        {
            glProgramUniform4fv(id, location, count, value);
        }

        void Program::uniformVector1(int location, int count, const int* value)
        {
            glProgramUniform1iv(id, location, count, value);
        }

        void Program::uniformVector2(int location, int count, const int* value)
        {
            glProgramUniform2iv(id, location, count, value);
        }

        void Program::uniformVector3(int location, int count, const int* value)
        {
            glProgramUniform3iv(id, location, count, value);
        }

        void Program::uniformVector4(int location, int count, const int* value)
        {
            glProgramUniform4iv(id, location, count, value);
        }

        void Program::uniformVector1(int location, int count, const unsigned int* value)
        {
            glProgramUniform1uiv(id, location, count, value);
        }

        void Program::uniformVector2(int location, int count, const unsigned int* value)
        {
            glProgramUniform2uiv(id, location, count, value);
        }

        void Program::uniformVector3(int location, int count, const unsigned int* value)
        {
            glProgramUniform3uiv(id, location, count, value);
        }

        void Program::uniformVector4(int location, int count, const unsigned int* value)
        {
            glProgramUniform4uiv(id, location, count, value);
        }

        void Program::uniformMatrix2x2(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix2fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix3x3(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix3fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix4x4(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix4fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix2x3(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix2x3fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix3x2(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix3x2fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix2x4(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix2x4fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix4x2(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix4x2fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix3x4(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix3x4fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }

        void Program::uniformMatrix4x3(int location, int count, bool transpose, const float* value)
        {
            glProgramUniformMatrix4x3fv(id, location, count, (GLboolean) (transpose ? GL_TRUE : GL_FALSE), value);
        }
    }
}