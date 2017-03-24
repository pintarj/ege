#include <ege/engine/resources.hxx>
#include <private/ege/engine/resources.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/version.hxx>
#include <ege/exception.hxx>
#include <ege/flow/enqueue-executor.hxx>
#include <private/ege/engine/control-thread.hxx>
#include <private/ege/engine/ini-fini.hxx>
#include <private/ege/flow/ege-start-scene.hxx>
#include <private/ege/flow/event-update-fragment.hxx>
#include <private/ege/flow/origin-fragment.hxx>
#include <private/ege/glfw/monitor.hxx>
#include <private/ege/glfw/window.hxx>
#include <private/ege/opengl/error.hxx>

namespace ege
{
    namespace engine
    {
        static log::Logger logger;
        static const std::vector<std::unique_ptr<hardware::Monitor>>* monitors;
        static opengl::Context* openglContext;
        static flow::PriorityExecutor* graphicExecutor;
        static keyboard::Keyboard* keyboard;
        static std::shared_ptr<flow::Fragment> eventUpdateFragment;
        static flow::ParallelNucleus* parallelNucleus;
        static flow::FPSAnalyzer* fpsAnalyzer;

        static glfw::Window* window;
        static std::shared_ptr<flow::SyncExecutionQueue> graphicExecutionQueue;
        static engine::ControlThread* controlThread;
        static flow::OriginFragment* originFragment;

        class IF: engine::IniFini
        {
            public:
                virtual void initialize() override
                {
                    monitors                = nullptr;
                    openglContext           = nullptr;
                    graphicExecutor         = nullptr;
                    keyboard                = nullptr;
                    eventUpdateFragment     = std::shared_ptr<flow::Fragment>(nullptr);
                    parallelNucleus         = nullptr;
                    fpsAnalyzer             = nullptr;
                    window                  = nullptr;
                    graphicExecutionQueue   = std::shared_ptr<flow::SyncExecutionQueue>(nullptr);
                    controlThread           = nullptr;
                    originFragment          = nullptr;
                }

                virtual void terminate() override
                {
                    delete originFragment;
                    delete controlThread;
                    delete window;
                    delete fpsAnalyzer;
                    delete parallelNucleus;
                    eventUpdateFragment = std::shared_ptr<flow::Fragment>(nullptr);
                    delete graphicExecutor;
                    graphicExecutionQueue = std::shared_ptr<flow::SyncExecutionQueue>(nullptr);
                    glfwTerminate();
                    opengl::checkError("OpenGL error during engine termination");
                }
        }
        static resourcesIniFini;

        log::Logger& getLogger()
        {
            return logger;
        }

        const std::vector<std::unique_ptr<hardware::Monitor>>& getMonitors()
        {
            return *monitors;
        }

        hardware::Monitor& getPrimaryMonitor()
        {
            return *monitors->at(0);
        }

        flow::PriorityExecutor& getGraphicExecutor()
        {
            return *graphicExecutor;
        }

        opengl::Context& getOpenglContext()
        {
            return *openglContext;
        }

        keyboard::Keyboard& getKeyboard()
        {
            return *keyboard;
        }

        static inline void initializeGLFW()
        {
            if (glfwInit() == GLFW_FALSE)
                exception::throwNew("couldn't initialize GLFW");

            int glfwVersion[3];
            glfwGetVersion(&glfwVersion[0], &glfwVersion[1], &glfwVersion[2]);
            engine::getLogger().log(log::Level::INFO, "GLFW %d.%d.%d initialized", glfwVersion[0], glfwVersion[1], glfwVersion[2]);
        }

        static inline void initializeWindow(Configuration& configuration)
        {
            std::string title = configuration.getApplicationName();

            if (configuration.isFullscreenPreferred())
            {
                window = new glfw::Window(title, configuration.getPreferredVideoMode());
            }
            else
            {
                Configuration::WindowCreation c = configuration.getPreferredWindowCreationParams();
                window = new glfw::Window(title, c.width, c.height, c.resizable);
            }
        }

        static inline std::shared_ptr<flow::Scene> configureInitialScene(Configuration& configuration)
        {
            std::shared_ptr<flow::Scene> initial = configuration.createInitialScene();

            if (initial.get() == nullptr)
                ege::exception::throwNew("no initial scene defined");

            if (!configuration.skipStartScene())
                initial = std::shared_ptr<flow::Scene>(new flow::EGEStartScene(initial));
            else
                getLogger().log(log::Level::INFO, "EGE start scene skipped");

            return initial;
        }

        static inline void printVersion()
        {
            uint32_t egeVersion[3];
            version::get(&egeVersion[0], &egeVersion[1], &egeVersion[2]);
            logger.log(log::Level::INFO, "EGE %d.%d.%d initialized", egeVersion[0], egeVersion[1], egeVersion[2]);
        }

        void initializeAndConfigure(Configuration& configuration)
        {
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

            {
                initializeGLFW();
                monitors                    = &glfw::Monitor::getMonitors();
                graphicExecutionQueue       = std::shared_ptr<flow::SyncExecutionQueue>(new flow::SyncExecutionQueue());
                graphicExecutor             = new flow::EnqueueExecutor(graphicExecutionQueue);
                initializeWindow(configuration);
                openglContext               = &window->getContext();
                keyboard                    = &window->getKeyboard();
                parallelNucleus             = new flow::ParallelNucleus;
                fpsAnalyzer                 = new flow::FPSAnalyzer;
                eventUpdateFragment         = std::shared_ptr<flow::Fragment>(new flow::EventUpdateFragment);
                auto initialScene           = configureInitialScene(configuration);
                controlThread               = new engine::ControlThread(initialScene);
                originFragment              = new flow::OriginFragment(initialScene);
                opengl::checkError("OpenGL error during engine initialization");
                printVersion();
                engine::getGLFWWindow().show();
            }

            std::chrono::duration<float> delta = std::chrono::system_clock::now() - start;
            logger.log(log::Level::INFO, "engine initialized and configured (in %.3fs)", delta.count());
        }

        glfw::Window& getGLFWWindow()
        {
            return *window;
        }

        flow::SyncExecutionQueue& getGraphicExecutionQueue()
        {
            return *graphicExecutionQueue;
        }

        engine::ControlThread& getControlThread()
        {
            return *controlThread;
        }

        flow::OriginFragment& getOriginFragment()
        {
            return *originFragment;
        }

        std::shared_ptr<flow::Fragment> getEventUpdateFragment()
        {
            return eventUpdateFragment;
        }

        flow::ParallelNucleus& getParallelNucleus()
        {
            return *parallelNucleus;
        }

        const flow::FPSAnalyzer& getFPSAnalyzer()
        {
            return getNonConstFPSAnalyzer();
        }

        flow::FPSAnalyzer& getNonConstFPSAnalyzer()
        {
            return *fpsAnalyzer;
        }
    }
}
