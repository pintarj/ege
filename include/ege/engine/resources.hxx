

#ifndef EGE_ENGINE_RESOURCES_HXX
#define EGE_ENGINE_RESOURCES_HXX


#include <ege/hardware/monitor.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/resource/manager.hxx>


namespace ege
{
        namespace engine
        {
                struct Resources
                {
                        hardware::Monitor* monitor;
                        util::fps::Analyzer* fpsAnalyzer;
                        resource::Manager* resourcesManager;
                };
        }
}


#endif
