

#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX


#include <ege/scenario.hxx>
#include <ege/engine/configuration.hxx>
#include <ege/engine/resources.hxx>


namespace ege
{
        class Scenario;

        namespace engine
        {
                extern Configuration configuration;
                extern Resources resources;

                void initialize();
                void start( Scenario* initialScenario );
                void destroy();
        }
}


#endif
