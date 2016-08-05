#include <ege/engine.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>


#define CAST_WIN ( ( GLFWwindow* ) win )


using namespace ege;
using namespace ege::graphic;


class DefaultCanvas: public Canvas
{
        public:
                DefaultCanvas( size_t width, size_t height ): Canvas( true, width, height )
                {

                }

                ~DefaultCanvas() {}
};


static Engine* engine;


Engine::Engine()
{
        glfwInit();
        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode( primary );
        win = glfwCreateWindow( videoMode->width, videoMode->height, "", primary, NULL );
        glfwMakeContextCurrent( CAST_WIN );
        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();
        resources = new EngineResources;
        resources->screen = new DefaultCanvas( ( size_t ) videoMode->width, ( size_t ) videoMode->height );
}


Engine& Engine::getReference()
{
        if ( engine == nullptr )
                engine = new Engine;

        return *engine;
}


Engine::~Engine()
{
        delete resources->screen;
        delete resources;
        glfwDestroyWindow( CAST_WIN );
        glfwTerminate();
}


void Engine::start( Scenario* initialScenario )
{
        Scenario* current = initialScenario;

        while ( true )
        {
                glfwPollEvents();

                if ( glfwWindowShouldClose( CAST_WIN ) )
                {
                        current->shouldClose();

                        if ( current->isNextScenarioAvailable() )
                                goto should_close_jump;
                }

                current->update();

                if ( current->isNextScenarioAvailable() )
                {
                        should_close_jump:
                        current = current->getNextScenario();

                        if ( current == nullptr )
                                break;
                }

                glfwSwapBuffers( CAST_WIN );
                std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
        }
}


EngineResources* Engine::getResources()
{
        return resources;
}
