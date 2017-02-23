
#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX

#include <memory>
#include <vector>
#include <ege/log.hxx>
#include <ege/keyboard.hxx>
#include <ege/flow/executor.hxx>
#include <ege/flow/scene.hxx>
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
                 * \brief The window creation configuration class.
                 * */
                class WindowCreation
                {
                    public:
                        /**
                         * \brief The window width. Default is 800.
                         * */
                        int width;

                        /**
                         * \brief The window height. Default is 600.
                         * */
                        int height;

                        /**
                         * \brief Tells if window is resizable. Default is true.
                         * */
                        bool resizable;

                        /**
                         * \brief Create a default window creation configuration.
                         * */
                        WindowCreation();
                };

                /**
                 * \brief Creates and returns the initial scene.
                 * \return The initial scene.
                 * */
                virtual std::shared_ptr<flow::Scene> createInitialScene() = 0;

                /**
                 * \brief Returns the application name.
                 * \return The application name.
                 * */
                virtual const std::string getApplicationName();

                /**
                 * \brief Tells if the start engine scene has to be skipped.
                 * \return \c True if it has to be skipped.
                 *
                 * The default implementations returns \c false.
                 * */
                virtual bool skipStartScene();

                /**
                 * \brief Tells if the fullscreen is preferred over the windowed mode.
                 * \return \c True if the fullscreen is preferred.
                 *
                 * The default implementations returns \c true.
                 * */
                virtual bool isFullscreenPreferred();

                /**
                 * \brief Returns the preferred video mode of a monitor when creating a fullscreen application.
                 * \return The preferred video mode of a monitor.
                 * \sa isFullscreenPreferred()
                 *
                 * Used to create a fullscreen application when isFullscreenPreferred() returns \c true.
                 * The default implementations returns the current video mode of primary monitor.
                 * */
                virtual const hardware::VideoMode& getPreferredVideoMode();

                /**
                 * \brief Returns the preferred window creation parameters when creating a windowed application.
                 * \return The preferred window creation parameters.
                 * \sa isFullscreenPreferred()
                 *
                 * Used to create a windowed application when isFullscreenPreferred() returns \c false.
                 * The default implementation returns a default WindowCreation object.
                 * */
                virtual WindowCreation getPreferredWindowCreationParams();
        };

        extern util::fps::Analyzer* fpsAnalyzer;
        extern util::fps::Moderator* fpsModerator;
        extern log::Logger* logger;
        extern opengl::Context* openglContext;
        extern const std::vector<std::unique_ptr<hardware::Monitor>>* monitors;
        extern const hardware::Monitor* primaryMonitor;
        extern keyboard::Keyboard* keyboard;
        extern flow::Executor* graphicExecutor;

        /**
         * \brief Starts an engine using a specific configuration.
         * \param configuration The engine configuration.
         * */
        void start(Configuration& configuration);
    }
}

#endif
