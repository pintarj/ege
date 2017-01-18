#include <ege/version.hxx>

namespace ege
{
    namespace version
    {
        void get(unsigned* major, unsigned* minor, unsigned* build)
        {
            if (major != nullptr)
                *major = EGE_VERSION_MAJOR;

            if (minor != nullptr)
                *minor = EGE_VERSION_MINOR;

            if (build != nullptr)
                *build = EGE_VERSION_BUILD;
        }
    }
}
