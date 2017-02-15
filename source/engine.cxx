#include <ege/engine.hxx>
#include <atomic>
#include <chrono>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/exception.hxx>
#include <ege/version.hxx>
#include <private/ege/game/ege-start-scene.hxx>
#include <private/ege/graphic/font/library.hxx>
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
        static std::shared_ptr<game::Scene>     currentScene;
        static glfw::Window*                    window;
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
                global::currentScene = std::shared_ptr<game::Scene>(new game::EGEStartScene(global::currentScene));
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
                graphic::font::library::initialize();
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
                    global::currentScene = global::currentScene->getNextScene();
                }
                else
                {
                    global::currentScene->render();
                    global::window->swapBuffers();
                    engine::fpsModerator->moderate();
                }

                engine::checkGLErrors("OpenGL error during engine execution");
                engine::fpsAnalyzer->calculateDeltaAndMark();
            }

            engine::logger->log(log::Level::INFO, "engine loop stopped");
        }

        static inline void destroy()
        {
            delete global::window;
            delete fpsModerator;
            delete fpsAnalyzer;
            graphic::font::library::destroy();
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
                    logger->log(log::Level::INFO, "engine started");
                    initializeAndConfigure(configuration);
                    startLoop();
                    logger->log(log::Level::INFO, "engine stopped");

                    if (!global::restartRequired)
                        break;

                    logger->log(log::Level::INFO, "engine restarting");
                }

                destroy();
                global::started = false;
            }
            catch (ege::Exception e)
            {
                e.consume();
            }
        }
    }
}
