

#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX


#include <ege/game/scene.hxx>
#include <ege/hardware/keyboard.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/util/fps/moderator.hxx>
#include <ege/util/log/logger.hxx>
#include <functional>


namespace ege
{
        class Engine;

        namespace game
        {
                class Scene;
        }

        namespace graphic
        {
                namespace gpu
                {
                        class Context;
                }

        }

        namespace hardware
        {
                class Monitor;
        }

        namespace engine
        {
                struct Configurations
                {
                        std::function< game::Scene*() > createInitialScene;
                };

                struct Resources
                {
                        hardware::Monitor* const monitor;
                        util::fps::Analyzer* const fpsAnalyzer;
                        util::fps::Moderator* const fpsModerator;
                        util::log::Logger* const logger;

                        friend Engine;

                        private:
                                Resources();
                };

                extern Resources* resources;

                void start( const std::function< void( Configurations& ) >& configure );
        }

        class Engine
        {
                friend void engine::start( const std::function< void( engine::Configurations& ) >& configure );

                private:
                        Engine();
                        ~Engine();
                        void start();
        };
}


#endif
