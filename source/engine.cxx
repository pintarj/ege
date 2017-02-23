#include <ege/engine.hxx>
#include <atomic>
#include <chrono>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/exception.hxx>
#include <ege/version.hxx>
#include <ege/flow/enqueue-executor.hxx>
#include <ege/flow/execution-queue.hxx>
#include <ege/time/time-stamp.hxx>
#include <private/ege/flow/ege-start-scene.hxx>
#include <private/ege/glfw/monitor.hxx>
#include <private/ege/glfw/window.hxx>
#include <private/ege/glfw/keyboard.hxx>

namespace ege
{
    namespace global
    {
        static std::atomic_bool                 started(false);
        static bool                             restartRequired;
        static log::Logger                      logger;
        static std::shared_ptr<flow::Scene>     currentScene;
        static glfw::Window*                    window;
        static flow::SyncExecutionQueue         graphicExecutionQueue;
    }

    namespace engine
    {
        util::fps::Analyzer*                                    fpsAnalyzer;
        util::fps::Moderator*                                   fpsModerator;
        log::Logger*                                            logger = &global::logger;
        keyboard::Keyboard*                                     keyboard;
        const std::vector<std::unique_ptr<hardware::Monitor>>*  monitors;
        const hardware::Monitor*                                primaryMonitor;
        opengl::Context*                                        openglContext;
        flow::Executor*                                         graphicExecutor;

        Configuration::WindowCreation::WindowCreation()
        {
            width = 800;
            height = 600;
            resizable = true;
        }

        const std::string Configuration::getApplicationName()
        {
            return "EGE application";
        }

        bool Configuration::skipStartScene()
        {
            return false;
        }

        bool Configuration::isFullscreenPreferred()
        {
            return true;
        }

        const hardware::VideoMode& Configuration::getPreferredVideoMode()
        {
            return monitors->at(0)->getCurrentVideoMode();
        }

        Configuration::WindowCreation Configuration::getPreferredWindowCreationParams()
        {
            return Configuration::WindowCreation();
        }

        static inline void checkGLErrors(const std::string& message)
        {
            GLenum glError = glGetError();

            if (glError != GL_NO_ERROR)
                ege::exception::throwNew("%s (code: %d)", message.c_str(), glError);
        }

        static inline void initializeGLFW()
        {
            if (glfwInit() == GLFW_FALSE)
                ege::exception::throwNew("couldn't initialize GLFW");

            int glfwVersion[3];
            glfwGetVersion(&glfwVersion[0], &glfwVersion[1], &glfwVersion[2]);
            logger->log(log::Level::INFO, "GLFW %d.%d.%d initialized", glfwVersion[0], glfwVersion[1], glfwVersion[2]);
        }

        static inline void initializeWindow(Configuration& configuration)
        {
            std::string title = configuration.getApplicationName();

            if (configuration.isFullscreenPreferred())
            {
                global::window = new glfw::Window(title, configuration.getPreferredVideoMode());
            }
            else
            {
                Configuration::WindowCreation c = configuration.getPreferredWindowCreationParams();
                global::window = new glfw::Window(title, c.width, c.height, c.resizable);
            }
        }

        static inline void configureInitialScene(Configuration& configuration)
        {
            global::currentScene = configuration.createInitialScene();

            if (global::currentScene.get() == nullptr)
                ege::exception::throwNew("no initial scene defined");

            if (!configuration.skipStartScene())
                global::currentScene = std::shared_ptr<flow::Scene>(new flow::EGEStartScene(global::currentScene));
            else
                engine::logger->log(log::Level::INFO, "EGE start scene skipped");
        }

        static inline void initializeAndConfigure(Configuration& configuration)
        {
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

            {
                global::restartRequired     = false;
                initializeGLFW();
                monitors                    = &glfw::Monitor::getMonitors();
                primaryMonitor              = monitors->at(0).get();
                fpsAnalyzer                 = new util::fps::Analyzer;
                fpsModerator                = new util::fps::Moderator(*fpsAnalyzer);
                initializeWindow(configuration);
                openglContext               = &global::window->getContext();
                keyboard                    = &global::window->getKeyboard();
                graphicExecutor             = new flow::EnqueueExecutor(global::graphicExecutionQueue);
                configureInitialScene(configuration);
                checkGLErrors("OpenGL error during engine initialization");

                uint32_t egeVersion[3];
                version::get(&egeVersion[0], &egeVersion[1], &egeVersion[2]);
                engine::logger->log(log::Level::INFO, "EGE %d.%d.%d initialized", egeVersion[0], egeVersion[1], egeVersion[2]);
            }

            std::chrono::duration<float> delta = std::chrono::system_clock::now() - start;
            logger->log(log::Level::INFO, "engine initialized and configured (in %.3fs)", delta.count());
        }

        static inline void startLoop()
        {
            engine::logger->log(log::Level::INFO, "engine loop started");
            global::window->show();
            engine::fpsAnalyzer->calculateDeltaAndMark();
            engine::fpsAnalyzer->setLastDelta(1.0f / 60.0f);

            while (true)
            {
                glfwPollEvents();
                glfwPollEvents(); // solve bug: glfw perform a key repressed after key repeating

                if (global::window->shouldClose())
                {
                    global::currentScene->shouldClose();

                    if (global::currentScene->isStopRequired())
                        goto stop_engine_label;
                }

                global::currentScene->update(engine::fpsAnalyzer->getLastDelta());

                if (global::currentScene->isStopRequired())
                {
            stop_engine_label:
                    global::restartRequired = global::currentScene->isRestartRequired();
                    break;
                }

                if (global::currentScene->getNextScene() != nullptr)
                {
                    std::shared_ptr<flow::Scene> nextScene = global::currentScene->getNextScene();
                    const char* currentId = global::currentScene->getIdentification().c_str();
                    const char* nextId = nextScene->getIdentification().c_str();
                    engine::logger->log(log::Level::INFO, "scene change required (%s -> %s)", currentId, nextId);
                    global::currentScene = nextScene;

                    // For debug purposes the currentId is "recalculated" instead of using nextId.
                    currentId = global::currentScene->getIdentification().c_str();
                    engine::logger->log(log::Level::INFO, "new current scene: %s ", currentId);
                }
                else
                {
                    global::currentScene->render();
                    global::window->swapBuffers();
                    while (global::graphicExecutionQueue.executeOne());
                    engine::fpsModerator->moderate();
                }

                engine::checkGLErrors("OpenGL error during engine execution");
                engine::fpsAnalyzer->calculateDeltaAndMark();
            }

            engine::logger->log(log::Level::INFO, "engine loop stopped");
        }

        static inline void destroy()
        {
            delete graphicExecutor;
            delete global::window;
            delete fpsModerator;
            delete fpsAnalyzer;
            glfwTerminate();
            checkGLErrors("OpenGL error during engine termination");
        }

        void start(Configuration& configuration)
        {
            try
            {
                if (global::started.exchange(true))
                    ege::exception::throwNew("an attempt to start engine was done, but engine is already started");

                while (true)
                {
                    time::TimeStamp<float> stamp;
                    logger->log(log::Level::INFO, "engine started");
                    initializeAndConfigure(configuration);
                    startLoop();
                    destroy();
                    logger->log(log::Level::INFO, "engine stopped (uptime: %.3fs)", stamp.getElapsed());

                    if (!global::restartRequired)
                        break;

                    logger->log(log::Level::INFO, "engine restarting");
                }

                global::started = false;
            }
            catch (ege::Exception e)
            {
                e.consume();
                logger->log(log::Level::ERROR, "engine has ended in unexpected way (unhandled exception)");
            }
        }
    }
}
