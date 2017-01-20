
#ifndef EGE_OPENGL_SHADER_HXX
#define EGE_OPENGL_SHADER_HXX

#include <string>
#include <ege/opengl/object.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumeration of Shader types.
         * */
        enum class ShaderType
        {
            FRAGMENT    = 0x8B30,
            VERTEX      = 0x8B31,
            GEOMETRY    = 0x8DD9
        };

        /**
         * \brief Wrapper for the OpenGL shader object.
         * \sa ege::opengl::Program
         *
         * Shaders are non movable or copyable.
         * */
        class Shader: public Object<unsigned int>
        {
            public:
                /**
                 * \brief Create a shader object of a specific type and with specific code.
                 * \param type The type of the shader.
                 * \param code The code written in GLSL that will be compiled.
                 *
                 * The constructor will compile the code written in GLSL on the GPU. If an error
                 * happens during compilation, then an ege::Exception will be thrown.
                 * */
                Shader(ShaderType type, const std::string& code);

                Shader(Shader&&) = delete;
                Shader(const Shader&) = delete;
                virtual ~Shader();
        };
    }
}

#endif
