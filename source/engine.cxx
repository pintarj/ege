#include <ege/engine.hxx>
#include <ege/exception.hxx>
#include <ege/graphic/gpu/context.hxx>
#include <ege/util/log/logger.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <atomic>


using namespace ege;


engine::Resources* ege::engine::resources;


namespace global
{
        static std::atomic_bool started( false );
        static engine::Configurations configurations;
        static hardware::Monitor* monitor;
        static util::fps::Analyzer* fpsAnalyzer;
        static util::fps::Moderator* fpsModerator;
        static util::log::Logger logger;
        static bool restartRequired;
}


static void initializeStaticMembers()
{
        ege::engine::resources = nullptr;
        global::configurations.createInitialScene = [] () { return nullptr; };
        global::monitor = nullptr;
        global::fpsAnalyzer = nullptr;
        global::fpsModerator = nullptr;
        global::logger.setLevel( util::log::Level::INFO );
        global::restartRequired = false;
}


engine::Resources::Resources():
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
                        Exception::throwNew( "an attempt to start engine was done, but engine is already started" );

                while ( true )
                {
                        global::logger.log( util::log::Level::INFO, "engine started" );
                        initializeStaticMembers();
                        configure( global::configurations );
                        Engine* engine = new Engine();
                        engine->start();
                        delete engine;

                        if ( global::restartRequired )
                        {
                                global::logger.log( util::log::Level::INFO, "engine restarting" );
                                continue;
                        }

                        global::logger.log( util::log::Level::INFO, "engine stopped" );
                        break;
                }

                global::started = false;
        }
        catch ( ege::Exception* e )
        {
                e->consume();
        }
}


Engine::Engine()
{
        glfwInit();
        global::monitor = new hardware::Monitor( glfwGetPrimaryMonitor() );
        global::fpsAnalyzer = new util::fps::Analyzer();
        global::fpsModerator = new util::fps::Moderator( *global::fpsAnalyzer, 60 );
        ege::engine::resources = new engine::Resources();
}


Engine::~Engine()
{
        delete ege::engine::resources;
        delete global::fpsModerator;
        delete global::fpsAnalyzer;
        delete global::monitor;
        glfwTerminate();

        GLenum glError = GL_NO_ERROR;

        if ( ( glError = glGetError() ) != GL_NO_ERROR )
                Exception::throwNew( "GL error (%d) during engine termination", glError );
}


void Engine::start()
{
        GLenum glError = GL_NO_ERROR;

        global::monitor->createGPUContext();
        graphic::gpu::frameBuffer::setClearColor( 0.0, 0.0, 0.0, 0.0 );
        global::monitor->getGPUContext().getDefaultFrameBuffer().bindAsDrawTarget();
        game::Scene* currentScene = global::configurations.createInitialScene();

        if ( currentScene == nullptr )
                Exception::throwNew( "no initial scenario defined" );

        global::fpsAnalyzer->calculateDeltaAndMark();
        global::fpsAnalyzer->setLastDelta( 1.0f / 60.0f );

        if ( ( glError = glGetError() ) != GL_NO_ERROR )
                Exception::throwNew( "GL error (%d) during engine initialization", glError );

        global::logger.log( util::log::Level::INFO, "engine loop started" );

        while ( true )
        {
                glfwPollEvents();

                if ( glfwWindowShouldClose( static_cast< GLFWwindow* >( global::monitor->getGPUContext().glfwContext ) ) )
                {
                        currentScene->shouldClose();

                        if ( currentScene->stopEngine )
                                goto stop_engine_label;
                }

                currentScene->update( global::fpsAnalyzer->getLastDelta() );

                if ( currentScene->stopEngine )
                {
stop_engine_label:
                        global::restartRequired = currentScene->restartEngine;
                        break;
                }

                if ( currentScene->nextScene != nullptr )
                {
                        currentScene = currentScene->nextScene;
                }
                else
                {
                        currentScene->render();
                        global::monitor->getGPUContext().swapBuffers();
                        global::fpsModerator->moderate();
                }

                if ( ( glError = glGetError() ) != GL_NO_ERROR )
                        Exception::throwNew( "GL error (%d) during engine execution", glError );

                global::fpsAnalyzer->calculateDeltaAndMark();
        }

        global::logger.log( util::log::Level::INFO, "engine loop stopped" );
}