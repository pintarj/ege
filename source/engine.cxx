#include <ege/engine.hxx>
#include <ege/exception.hxx>
#include <ege/version.hxx>
#include <ege/graphic/gpu/context.hxx>
#include <private/ege/graphic/font/library.hxx>
#include <private/ege/game/ege-start-scene.hxx>
#include <ege/util/log/logger.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <atomic>
#include <chrono>


using namespace ege;


engine::Resources* ege::engine::resources;


namespace global
{
        static std::atomic_bool started( false );
        static engine::Configurations configurations;
        static hardware::Keyboard* keyboard;
        static hardware::Monitor* monitor;
        static util::fps::Analyzer* fpsAnalyzer;
        static util::fps::Moderator* fpsModerator;
        static util::log::Logger logger;
        static game::Scene* currentScene;
        static bool restartRequired;
}


static void initializeStaticMembers()
{
        ege::engine::resources = nullptr;
        global::configurations.createInitialScene = [] () { return nullptr; };
        global::keyboard = nullptr;
        global::monitor = nullptr;
        global::fpsAnalyzer = nullptr;
        global::fpsModerator = nullptr;
        global::logger.setLevel( util::log::Level::INFO );
        global::currentScene = nullptr;
        global::restartRequired = false;
}


engine::Resources::Resources():
        keyboard( global::keyboard ),
        monitor( global::monitor ),
        fpsAnalyzer( global::fpsAnalyzer ),
        fpsModerator( global::fpsModerator ),
        logger( &global::logger )
{

}


void engine::start( const std::function< void( engine::Configurations& ) > &configure )
{
        try
        {
                if ( global::started.exchange( true ) )
                        ege::exception::throwNew( "an attempt to start engine was done, but engine is already started" );

                while ( true )
                {
                        std::chrono::time_point< std::chrono::system_clock > start = std::chrono::system_clock::now();
                        global::logger.log( util::log::Level::INFO, "engine started" );
                        initializeStaticMembers();
                        configure( global::configurations );
                        Engine* engine = new Engine();
                        std::chrono::duration< float > delta = std::chrono::system_clock::now() - start;
                        global::logger.log( util::log::Level::INFO, "engine initialized and configured (in %.3fs)", delta.count() );
                        engine->start();
                        delete engine;
                        global::logger.log( util::log::Level::INFO, "engine stopped" );

                        if ( ! global::restartRequired )
                                break;

                        global::logger.log( util::log::Level::INFO, "engine restarting" );
                }

                global::started = false;
        }
        catch ( ege::Exception e )
        {
                e.consume();
        }
}


Engine::Engine()
{
        if( glfwInit() == GL_FALSE )
                ege::exception::throwNew( "could not initialize GLFW" );

        int glfwVersion[ 3 ];
        glfwGetVersion( &glfwVersion[ 0 ], &glfwVersion[ 1 ], &glfwVersion[ 2 ] );
        global::logger.log( util::log::Level::INFO, "GLFW %d.%d.%d initialized", glfwVersion[ 0 ], glfwVersion[ 1 ], glfwVersion[ 2 ] );

        global::monitor = new hardware::Monitor( glfwGetPrimaryMonitor() );
        global::fpsAnalyzer = new util::fps::Analyzer();
        global::fpsModerator = new util::fps::Moderator( *global::fpsAnalyzer, 60 );
        global::keyboard = new hardware::Keyboard();
        ege::engine::resources = new engine::Resources();

        graphic::font::library::initialize();

        global::monitor->createGPUContext();
        graphic::gpu::frameBuffer::setClearColor( 0.0, 0.0, 0.0, 0.0 );
        global::monitor->getGPUContext().getDefaultFrameBuffer().bindAsDrawTarget();
        void* glfwWindows[ 1 ] = { global::monitor->getGPUContext().glfwContext };
        global::keyboard->listenOnWindows( glfwWindows, 1 );

        global::currentScene = global::configurations.createInitialScene();
        global::currentScene = new game::EGEStartScene( *global::currentScene );

        if ( global::currentScene == nullptr )
                ege::exception::throwNew( "no initial scenario defined" );

        GLenum glError = glGetError();

        if ( glError != GL_NO_ERROR )
                ege::exception::throwNew( "GL error (%d) during engine initialization", glError );

        uint32_t egeVersion[ 3 ];
        version::get( &egeVersion[ 0 ], &egeVersion[ 1 ], &egeVersion[ 2 ] );
        global::logger.log( util::log::Level::INFO, "EGE %d.%d.%d initialized", egeVersion[ 0 ], egeVersion[ 1 ], egeVersion[ 2 ] );
        global::fpsAnalyzer->calculateDeltaAndMark();
        global::fpsAnalyzer->setLastDelta( 1.0f / 60.0f );
}


Engine::~Engine()
{
        delete ege::engine::resources;
        delete global::fpsModerator;
        delete global::fpsAnalyzer;
        delete global::monitor;
        delete global::keyboard;
        graphic::font::library::destroy();
        glfwTerminate();

        GLenum glError = glGetError();

        if ( glError != GL_NO_ERROR )
                ege::exception::throwNew( "GL error (%d) during engine termination", glError );
}


void Engine::start()
{
        global::logger.log( util::log::Level::INFO, "engine loop started" );

        while ( true )
        {
                glfwPollEvents();
                glfwPollEvents(); // solve bug: glfw perform a key repressed after key repeating

                if ( glfwWindowShouldClose( static_cast< GLFWwindow* >( global::monitor->getGPUContext().glfwContext ) ) )
                {
                        global::currentScene->shouldClose();

                        if ( global::currentScene->stopEngine )
                                goto stop_engine_label;
                }

                global::currentScene->update( global::fpsAnalyzer->getLastDelta() );

                if ( global::currentScene->stopEngine )
                {
stop_engine_label:
                        global::restartRequired = global::currentScene->restartEngine;

                        if ( global::currentScene->deleteOnExchange )
                                delete global::currentScene;

                        break;
                }

                if ( global::currentScene->nextScene != nullptr )
                {
                        game::Scene* previousScene = global::currentScene;
                        global::currentScene = previousScene->nextScene;

                        if ( previousScene->deleteOnExchange )
                                delete previousScene;
                }
                else
                {
                        global::currentScene->render();
                        global::monitor->getGPUContext().swapBuffers();
                        global::fpsModerator->moderate();
                }

                GLenum glError = glGetError();

                if ( glError != GL_NO_ERROR )
                        ege::exception::throwNew( "GL error (%d) during engine execution", glError );

                global::fpsAnalyzer->calculateDeltaAndMark();
        }

        global::logger.log( util::log::Level::INFO, "engine loop stopped" );
}