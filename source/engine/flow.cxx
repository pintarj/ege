#include <ege/engine/flow.hxx>
#include <private/ege/engine/flow.hxx>
#include <atomic>
#include <csignal>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/exception.hxx>
#include <ege/engine/resources.hxx>
#include <ege/time/time-stamp.hxx>
#include <private/ege/engine/ini-fini.hxx>
#include <private/ege/engine/resources.hxx>
#include <private/ege/flow/thread.hxx>
#include <private/ege/opengl/error.hxx>

#define EGE_GRAPHIC_ON_MAIN_THREAD (false)

namespace ege
{
    namespace engine
    {
        static std::atomic_bool started(false);
        static std::shared_ptr<flow::Scene> currentScene;
        static volatile bool sigTermReceived;
        static volatile bool stopRequired;
        static bool restartRequired;

        static void sigTermHandler(int x)
        {
            sigTermReceived = true;
            requireStop();
        }

        class FlowIniFini: IniFini
        {
            public:
                virtual void initialize() override
                {
                    currentScene    = std::shared_ptr<flow::Scene>(nullptr);
                    sigTermReceived = false;
                    stopRequired    = false;
                    restartRequired = false;
                    std::signal(SIGTERM, sigTermHandler);
                }

                virtual void terminate() override
                {
                    currentScene = std::shared_ptr<flow::Scene>(nullptr);
                }
        }
        static flowIniFini;

        static inline void startLoop()
        {
            auto& logger = engine::getLogger();
            auto& controlThread = engine::getControlThread();
            logger.log(log::Level::INFO, "engine loop started");
            engine::getControlThread().start();
            auto& queue = engine::getGraphicExecutionQueue();

            // The loop that is executing Executable objects from graphic queue.
            while (true)
            {
                while (queue.executeOne());

                if (stopRequired && !controlThread.isRunning())
                    break;

                opengl::checkError("OpenGL error during engine execution");
                queue.getNotEmptySignalWaiter().wait(100);
            }

            glFinish();
            logger.log(log::Level::DEBUG, "graphic execution stopped");
            controlThread.join();
            logger.log(log::Level::DEBUG, "control thread joined");
            logger.log(log::Level::INFO, "engine loop stopped");
        }

        void start(Configuration& configuration)
        {
            auto graphicExecutableBody = [&configuration]()
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
                };

#if EGE_GRAPHIC_ON_MAIN_THREAD
            graphicExecutableBody();
#else
            auto executable = std::shared_ptr<flow::Executable>(new flow::FunctionExecutable(graphicExecutableBody));
            engine::getLogger().log(log::Level::INFO, "using main thread as graphic thread");
            flow::Thread graphicThread(executable, "ege-graphic");
            graphicThread.start();
            graphicThread.join();
#endif
        }

        void requireStop() noexcept
        {
            if (sigTermReceived)
                engine::getLogger().log(log::Level::INFO, "SIGTERM received");

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
