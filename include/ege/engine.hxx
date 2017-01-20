
#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX

namespace ege
{
    class Engine;

    namespace engine
    {
        class Resources;
    }
}

#include <functional>
#include <memory>
#include <ege/log.hxx>
#include <ege/game/scene.hxx>
#include <ege/hardware/keyboard.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/util/fps/moderator.hxx>

namespace ege
{
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
        class Keyboard;
    }

    namespace engine
    {
        struct Configurations
        {
            std::function<std::shared_ptr<game::Scene>()> createInitialScene;
        };

        struct Resources
        {
                hardware::Keyboard* const keyboard;
                hardware::Monitor* const monitor;
                util::fps::Analyzer* const fpsAnalyzer;
                util::fps::Moderator* const fpsModerator;
                log::Logger* const logger;

                friend Engine;

            private:
                Resources();
        };

        extern Resources* resources;

        void start(const std::function<void(Configurations&)>& configure);
    }

    class Engine
    {
            friend void engine::start(const std::function<void(engine::Configurations&)>& configure);

        private:
            Engine();
            ~Engine();
            void start();
    };
}

#endif
