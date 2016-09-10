

#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX


#include <ege/game/scene.hxx>
#include <ege/hardware/keyboard.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/util/fps/moderator.hxx>
#include <functional>


namespace ege
{
        class Engine;

        namespace game
        {
                class Scene;
        }

        namespace engine
        {
                struct Configurations
                {
                        std::function< game::Scene*() > createInitialScene;
                };

                struct Resources
                {
                        hardware::Keyboard* const keyboard;
                        hardware::Monitor* const monitor;
                        util::fps::Analyzer* const fpsAnalyzer;
                        util::fps::Moderator* const fpsModerator;

                        friend Engine;

                        private:
                                Resources();
                };

                void start( const std::function< void( Configurations& ) > &configure );
        }

        class Engine
        {
                friend void engine::start( const std::function< void( engine::Configurations& ) > &configure );

                private:
                        Engine();
                        ~Engine();
                        void start();
        };
}


#endif
