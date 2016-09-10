#include <ege/engine.hxx>
#include <ege/exception.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <atomic>


using namespace ege;


class GLFWKeyboard: public hardware::Keyboard
{
        public:
                bool isPressed( hardware::keyboard::Key key );
};


namespace global
{
        static std::atomic_bool started( false );
        static engine::Configurations configurations;
        static GLFWKeyboard keyboard;
        static hardware::Monitor* monitor;
        static util::fps::Analyzer* fpsAnalyzer;
        static util::fps::Moderator* fpsModerator;
        static bool restartRequired;
        static GLFWwindow* glfwWindow;
}


bool GLFWKeyboard::isPressed( hardware::keyboard::Key key )
{
        return glfwGetKey( global::glfwWindow, ( int ) key ) == GLFW_PRESS;
}


static void initializeStaticMembers()
{
        global::configurations.createInitialScene = [] () { return nullptr; };
        global::monitor = nullptr;
        global::fpsAnalyzer = nullptr;
        global::fpsModerator = nullptr;
        global::restartRequired = false;
        global::glfwWindow = nullptr;
}


engine::Resources::Resources():
        keyboard( &global::keyboard ),
        monitor( global::monitor ),
        fpsAnalyzer( global::fpsAnalyzer ),
        fpsModerator( global::fpsModerator )
{

}


void engine::start( const std::function< void( engine::Configurations& ) > &configure )
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


Engine::Engine()
{
        glfwInit();
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode( primary );
        uint16_t monitorRefreshRate = ( uint16_t ) videoMode->refreshRate;
        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
        global::glfwWindow = glfwCreateWindow( videoMode->width, videoMode->height, "", primary, NULL );
        glfwMakeContextCurrent( global::glfwWindow );
        glfwSwapInterval( 1 );

        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();

        global::monitor = new hardware::Monitor( ( size_t ) videoMode->width, ( size_t ) videoMode->height );
        global::fpsAnalyzer = new util::fps::Analyzer();
        global::fpsModerator = new util::fps::Moderator( *global::fpsAnalyzer, monitorRefreshRate );

        *const_cast< engine::Resources** >( &ege::game::Scene::engineResources ) = new engine::Resources();
}


Engine::~Engine()
{
        glfwDestroyWindow( global::glfwWindow );
        delete global::fpsModerator;
        delete global::fpsAnalyzer;
        delete global::monitor;
        glfwTerminate();
}


void Engine::start()
{
        game::Scene* currentScene = global::configurations.createInitialScene();
        global::fpsAnalyzer->calculateDeltaAndMark();
        global::fpsAnalyzer->setLastDelta( 1.0f / 60.0f );

        while ( true )
        {
                glfwPollEvents();

                if ( glfwWindowShouldClose( global::glfwWindow ) )
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
                        glfwSwapBuffers( global::glfwWindow );
                        global::fpsModerator->moderate();
                }

                global::fpsAnalyzer->calculateDeltaAndMark();
        }
}
