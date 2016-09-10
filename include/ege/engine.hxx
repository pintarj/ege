

#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX


#include <ege/scenario/scenario.hxx>
#include <ege/hardware/keyboard.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/util/fps/moderator.hxx>
#include <functional>


namespace ege
{
        namespace engine
        {
                struct Configurations
                {
                        scenario::Scenario* initialScenario;
                };

                struct Resources
                {
                        hardware::Keyboard* keyboard;
                        hardware::Monitor* monitor;
                        util::fps::Analyzer* fpsAnalyzer;
                        util::fps::Moderator* fpsModerator;
                }
                extern resources;

                void start( const std::function< void( Configurations& ) >& configure );
        }
}


#endif
