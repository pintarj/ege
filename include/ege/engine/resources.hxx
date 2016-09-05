

#ifndef EGE_ENGINE_RESOURCES_HXX
#define EGE_ENGINE_RESOURCES_HXX


#include <ege/hardware/keyboard.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/util/fps/moderator.hxx>


namespace ege
{
        namespace engine
        {
                struct Resources
                {
                        hardware::Keyboard* keyboard;
                        hardware::Monitor* monitor;
                        util::fps::Analyzer* fpsAnalyzer;
                        util::fps::Moderator* fpsModerator;
                };
        }
}


#endif
