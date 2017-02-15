
#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX

#include <memory>
#include <vector>
#include <ege/log.hxx>
#include <ege/game/scene.hxx>
#include <ege/keyboard.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/opengl/context.hxx>
#include <ege/util/fps/analyzer.hxx>
#include <ege/util/fps/moderator.hxx>

namespace ege
{
    namespace engine
    {
        /**
         * \brief Stores the engine configurations.
         * */
        class Configuration
        {
            public:
                /**
                 * \brief Creates and returns the initial scene.
                 * \return The initial scene.
                 * */
                virtual std::shared_ptr<game::Scene> createInitialScene() = 0;

                /**
                 * \brief Returns the application name.
                 * \return The application name.
                 * */
                virtual const std::string getApplicationName();

                /**
                 * \brief Tells if the start engine scene has to be skipped.
                 * \return \c True if it has to be skipped.
                 * */
                virtual bool skipStartScene();
        };

        extern util::fps::Analyzer* fpsAnalyzer;
        extern util::fps::Moderator* fpsModerator;
        extern log::Logger* logger;
        extern opengl::Context* openglContext;
        extern const std::vector<std::unique_ptr<hardware::Monitor>>* monitors;
        extern const hardware::Monitor* primaryMonitor;
        extern keyboard::Keyboard* keyboard;

        /**
         * \brief Starts an engine using a specific configuration.
         * \param configuration The engine configuration.
         * */
        void start(Configuration& configuration);
    }
}

#endif
