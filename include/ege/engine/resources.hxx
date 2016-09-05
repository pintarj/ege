

#ifndef EGE_ENGINE_RESOURCES_HXX
#define EGE_ENGINE_RESOURCES_HXX


#include <ege/hardware/monitor.hxx>
#include <ege/resource/manager.hxx>


namespace ege
{
        namespace engine
        {
                struct Resources
                {
                        hardware::Monitor* monitor;
                        resource::Manager* resourcesManager;
                };
        }
}


#endif
