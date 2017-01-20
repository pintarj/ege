
#ifndef EGE_OPENGL_PROGRAM_HXX
#define EGE_OPENGL_PROGRAM_HXX

#include <initializer_list>
#include <ege/opengl/object.hxx>
#include <ege/opengl/shader.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Configuration structure for creation of Program objects.
         * */
        struct ProgramConfiguration
        {
            public:
                /**
                 * \brief The list of the shaders to link in program.
                 * */
                std::initializer_list<const Shader*> shaders;

                /**
                 * \brief Hint for the GPU if the binaries will be retrieved.
                 *
                 * Variable should be \c true to indicate to the implementation the intention of the application to
                 * retrieve (maybe in future) the program's binary representation. Default is \c false.
                 * */
                bool binaryRetrievableHint;

                /**
                 * \brief Tells if created program will be separable.
                 *
                 * Variable should be \c true to indicate whether program can be bound to individual pipeline stages.
                 * Default is \c false.
                 * */
                bool separable;

                /**
                 * \brief Setup the default configuration for the program.
                 * \sa Program
                 * */
                ProgramConfiguration();
        };

        /**
         * \brief Wrapper for the OpenGL program object.
         *
         * Certain methods are not commented (e.g. Program::uniformVector), that is because they
         * do only call the respective function in OpenGL (uniformVector -> glProgramUniform*).
         * Check the OpenGL documentation for more informations about these functions. \n
         * Program objects are non movable and non copyable.
         * */
        class Program: public Object<unsigned int>
        {
            public:
                /**
                 * \brief Create a Program object that is configured with an object of ProgramConfiguration.
                 * \param conf The configuration structure.
                 *
                 * How program creation works under the hood:
                 *  1. shaders are attached to program
                 *  2. program parameters are set (separable, binaryRetrievableHint)
                 *  3. program is linked
                 *  5. shaders are detached
                 *
                 * If an error happens during program linking, then an ege::Exception will be thrown.
                 * */
                Program(const ProgramConfiguration& conf);

                /**
                 * \brief Create a Program object that is linked using only the specified shaders.
                 * \param shaders The shaders that will be linked in program.
                 *
                 * If an error happens during program creation, then an ege::Exception will be thrown.
                 * */
                Program(std::initializer_list<const Shader*> shaders);

                Program(Program&&) = delete;
                Program(const Program&) = delete;
                virtual ~Program();

                /**
                 * \brief Installs the Program object as part of current rendering state.
                 * */
                void use() const;

                /**
                 * \brief Returns the location of a uniform variable.
                 * \return The location, or -1 if the location is not found.
                 * */
                int getUniformLocation(const std::string& name) const;

                void uniform(int location, float f0);
                void uniform(int location, float f0, float f1);
                void uniform(int location, float f0, float f1, float f2);
                void uniform(int location, float f0, float f1, float f2, float f3);
                void uniform(int location, int i0);
                void uniform(int location, int i0, int i1);
                void uniform(int location, int i0, int i1, int i2);
                void uniform(int location, int i0, int i1, int i2, int i3);
                void uniform(int location, unsigned int ui0);
                void uniform(int location, unsigned int ui0, unsigned int ui1);
                void uniform(int location, unsigned int ui0, unsigned int ui1, unsigned int ui2);
                void uniform(int location, unsigned int ui0, unsigned int ui1, unsigned int ui2, unsigned int ui3);
                void uniformVector1(int location, int count, const float* value);
                void uniformVector2(int location, int count, const float* value);
                void uniformVector3(int location, int count, const float* value);
                void uniformVector4(int location, int count, const float* value);
                void uniformVector1(int location, int count, const int* value);
                void uniformVector2(int location, int count, const int* value);
                void uniformVector3(int location, int count, const int* value);
                void uniformVector4(int location, int count, const int* value);
                void uniformVector1(int location, int count, const unsigned int* value);
                void uniformVector2(int location, int count, const unsigned int* value);
                void uniformVector3(int location, int count, const unsigned int* value);
                void uniformVector4(int location, int count, const unsigned int* value);
                void uniformMatrix2x2(int location, int count, bool transpose, const float* value);
                void uniformMatrix3x3(int location, int count, bool transpose, const float* value);
                void uniformMatrix4x4(int location, int count, bool transpose, const float* value);
                void uniformMatrix2x3(int location, int count, bool transpose, const float* value);
                void uniformMatrix3x2(int location, int count, bool transpose, const float* value);
                void uniformMatrix2x4(int location, int count, bool transpose, const float* value);
                void uniformMatrix4x2(int location, int count, bool transpose, const float* value);
                void uniformMatrix3x4(int location, int count, bool transpose, const float* value);
                void uniformMatrix4x3(int location, int count, bool transpose, const float* value);
        };
    }
}

#endif
