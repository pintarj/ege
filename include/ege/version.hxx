

#ifndef EGE_VERSION_HXX
#define EGE_VERSION_HXX


#define EGE_VERSION_MAJOR       0
#define EGE_VERSION_MINOR       1
#define EGE_VERSION_BUILD       0


#include <cstdint>


namespace ege
{
        namespace version
        {
                void get( uint32_t* major, uint32_t* minor, uint32_t* build );
        }
}


#endif
