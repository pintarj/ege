

#ifndef EGE_VERSION_HXX
#define EGE_VERSION_HXX


#define EGE_VERSION_MAJOR       ( 0 )
#define EGE_VERSION_MINOR       ( 1 )
#define EGE_VERSION_BUILD       ( 2 )


namespace ege
{
        namespace version
        {
                void get( unsigned* major, unsigned* minor, unsigned* build );
        }
}


#endif
