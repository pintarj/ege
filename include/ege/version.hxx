
#ifndef EGE_VERSION_HXX
#define EGE_VERSION_HXX

/**
 * \namespace ege::version
 * \brief Contains function to retrieve the library version.
 * */

#define EGE_VERSION_MAJOR   (0)
#define EGE_VERSION_MINOR   (1)
#define EGE_VERSION_BUILD   (2)

namespace ege
{
    namespace version
    {
        /**
         * \brief Retrieve the version number of the library.
         *
         * The version number will be stored in unsigned variables referenced by pointers passed as parameter.
         * If "nullptr" (aka NULL) is passed to any parameter, that respective version number wouldn't be retrieved. \n
         * Example of use, that retrieves only the "major" and "minor" version (without the "build"):
         * \code
         * unsigned major, minor;
         * ege::version::get(&major, &minor, nullptr);
         * \endcode
         * \param[out] major The pointer to a variable where the "major" version number will be stored.
         * \param[out] minor The pointer to a variable where the "minor" version number will be stored.
         * \param[out] build The pointer to a variable where the "build" version number will be stored.
         * */
        void get(unsigned* major, unsigned* minor, unsigned* build);
    }
}

#endif
