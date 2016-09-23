#include <ege/engine.hxx>
#include <ege/graphic/gpu/context.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <atomic>


using namespace ege;


namespace global
{
        static std::atomic_bool started( false );
        static engine::Configurations configurations;
        static hardware::Monitor* monitor;
        static util::fps::Analyzer* fpsAnalyzer;
        static util::fps::Moderator* fpsModerator;
        static bool restartRequired;
}


static void initializeStaticMembers()
{
        global::configurations.createInitialScene = [] () { return nullptr; };
        global::monitor = nullptr;
        global::fpsAnalyzer = nullptr;
        global::fpsModerator = nullptr;
        global::restartRequired = false;
}


engine::Resources::Resources():
        monitor( global::monitor ),
        fpsAnalyzer( global::fpsAnalyzer ),
        fpsModerator( global::fpsModerator )
{

}


void engine::start( const std::function< void( engine::Configurations& ) > &configure )
{
        try
        {
                if ( global::started.exchange( true ) )
                        exception::throwNew( "an attempt to start engine was done, but engine is already started" );

                do
                {
                        initializeStaticMembers();
                        configure( global::configurations );
                        Engine* engine = new Engine();
                        engine->start();
                        delete engine;
                }
                while ( global::restartRequired );

                global::started = false;
        }
        catch ( std::exception* e )
        {
                fprintf( stderr, "%s\n", e->what() );
        }
}


Engine::Engine()
{
        glfwInit();
        global::monitor = new hardware::Monitor( glfwGetPrimaryMonitor() );
        global::fpsAnalyzer = new util::fps::Analyzer();
        global::fpsModerator = new util::fps::Moderator( *global::fpsAnalyzer, 60 );
        ege::game::Scene::pointerToEngineResources = new engine::Resources();
}


Engine::~Engine()
{
        delete ege::game::Scene::pointerToEngineResources;
        delete global::fpsModerator;
        delete global::fpsAnalyzer;
        delete global::monitor;
        glfwTerminate();

        GLenum glError = GL_NO_ERROR;

        if ( ( glError = glGetError() ) != GL_NO_ERROR )
                exception::throwNew( "GL error (%d) during engine termination", glError );
}


void Engine::start()
{
        GLenum glError = GL_NO_ERROR;

        global::monitor->createGPUContext();
        global::monitor->getGPUContext().getDefaultFrameBuffer().bindAsDrawTarget();
        game::Scene* currentScene = global::configurations.createInitialScene();
        global::fpsAnalyzer->calculateDeltaAndMark();
        global::fpsAnalyzer->setLastDelta( 1.0f / 60.0f );

        if ( ( glError = glGetError() ) != GL_NO_ERROR )
                exception::throwNew( "GL error (%d) during engine initialization", glError );

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
                        exception::throwNew( "GL error (%d) during engine execution", glError );

                global::fpsAnalyzer->calculateDeltaAndMark();
        }
}