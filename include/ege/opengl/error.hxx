
#ifndef EGE_OPENGL_ERROR_HXX
#define EGE_OPENGL_ERROR_HXX

#include <string>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumerate the OpenGL errors.
         * */
        enum class Error: unsigned
        {
            NO_ERROR                        = 0x0000,
            INVALID_ENUM                    = 0x0500,
            INVALID_VALUE                   = 0x0501,
            INVALID_OPERATION               = 0x0502,
            STACK_OVERFLOW                  = 0x0503,
            STACK_UNDERFLOW                 = 0x0504,
            OUT_OF_MEMORY                   = 0x0505,
            INVALID_FRAMEBUFFER_OPERATION   = 0x0506,
            CONTEXT_LOST                    = 0x0507,
            TABLE_TOO_LARGE                 = 0x8031
        };

        /**
         * \brief Return error information (if any).
         * \return The error enumeration.
         * */
        Error getError();

        /**
         * \brief Convert the error code to the string representation.
         * \param error The error code.
         * \return The string representing the error code.
         * */
        std::string toString(Error error) noexcept;
    }
}

#endif
