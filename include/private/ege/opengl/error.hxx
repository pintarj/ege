
#ifndef PRIVATE_EGE_OPENGL_ERROR_HXX
#define PRIVATE_EGE_OPENGL_ERROR_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Check if an OpenGL error has occoured and eventually throws an error (or simply print it).
         * \param message The message that it will be used on error.
         * \param throwOnError If error has occoured an exception is thrown if it's \c true, if
         *     it's \c false it will be logged as an error (ege::log::Level::ERROR).
         * \throws ege::Exception If error has occoured and \c throwOnError is \c true.
         * */
        void checkError(const std::string& message, bool throwOnError = true);
    }
}

#endif
