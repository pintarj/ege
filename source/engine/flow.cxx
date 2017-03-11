#include <ege/engine/flow.hxx>
#include <private/ege/engine/flow.hxx>
#include <atomic>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/exception.hxx>
#include <ege/engine/resources.hxx>
#include <ege/time/time-stamp.hxx>
#include <private/ege/engine/ini-fini.hxx>
#include <private/ege/engine/resources.hxx>
#include <private/ege/opengl/error.hxx>

namespace ege
{
    namespace engine
    {
        static std::atomic_bool started(false);
        static std::shared_ptr<flow::Scene> currentScene;
        static bool stopRequired;
        static bool restartRequired;

        class IF: IniFini
        {
            public:
                virtual void initialize() override
                {
                    currentScene    = std::shared_ptr<flow::Scene>(nullptr);
                    stopRequired    = false;
                    restartRequired = false;
                }

                virtual void terminate() override
                {
                    currentScene = std::shared_ptr<flow::Scene>(nullptr);
                }
        }
        static flowIniFini;

        static inline void startLoop()
        {
            engine::getLogger().log(log::Level::INFO, "engine loop started");
            engine::getControlThread().start();
            auto& queue = engine::getGraphicExecutionQueue();

            // The loop that is executing Executable objects from graphic queue.
            while (true)
            {
                while (!stopRequired && queue.executeOne());

                if (stopRequired)
                    break;

                opengl::checkError("OpenGL error during engine execution");
                queue.getNotEmptySignalWaiter().wait(200);
            }

            engine::getControlThread().join();
            engine::getLogger().log(log::Level::INFO, "engine loop stopped");
        }

        void start(Configuration& configuration)
        {
            auto& logger = engine::getLogger();

            try
            {
                if (started.exchange(true))
                    ege::exception::throwNew("an attempt to start engine was done, but engine is already started");

                while (true)
                {
                    time::TimeStamp<float> stamp;
                    logger.log(log::Level::INFO, "engine started");
                    iniFini::initialize();
                    initializeAndConfigure(configuration);
                    startLoop();
                    iniFini::terminate();
                    logger.log(log::Level::INFO, "engine stopped (uptime: %.3fs)", stamp.getElapsed());

                    if (!restartRequired)
                        break;

                    logger.log(log::Level::INFO, "engine restarting");
                }

                started = false;
            }
            catch (ege::Exception e)
            {
                e.consume();
                logger.log(log::Level::ERROR, "engine has ended in unexpected way (unhandled exception)");
            }
        }

        void requireStop() noexcept
        {
            stopRequired = true;
            engine::getLogger().log(log::Level::INFO, "engine stop required");
        }

        void requireRestart() noexcept
        {
            restartRequired = true;
            stopRequired = true;
            engine::getLogger().log(log::Level::INFO, "engine restart required");
        }

        bool isStopRequired() noexcept
        {
            return stopRequired;
        }
    }
}
