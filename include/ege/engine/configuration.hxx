

#ifndef EGE_ENGINE_CONFIGURATION_HXX
#define EGE_ENGINE_CONFIGURATION_HXX


#include <ege/resource/root.hxx>


namespace ege
{
        namespace engine
        {
                struct Configuration
                {
                        resource::Root& root;

                        Configuration();
                        ~Configuration();
                };
        }
}


#endif
