#include <ege/version.hxx>


void ege::version::get( uint32_t* major, uint32_t* minor, uint32_t* build )
{
        if ( major != nullptr )
                *major = EGE_VERSION_MAJOR;

        if ( minor != nullptr )
                *minor = EGE_VERSION_MINOR;

        if ( build != nullptr )
                *build = EGE_VERSION_BUILD;
}