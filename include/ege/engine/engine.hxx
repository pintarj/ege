

#ifndef EGE_ENGINE_ENGINE_HXX
#define EGE_ENGINE_ENGINE_HXX


#include <ege/scenario/scenario.hxx>
#include <ege/engine/configuration.hxx>
#include <ege/engine/resources.hxx>


namespace ege
{
        namespace engine
        {
                extern Configuration configuration;
                extern Resources resources;

                void initialize();
                void start( scenario::Scenario* initialScenario );
                void destroy();
        }
}


#endif
