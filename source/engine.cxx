#include <ege/engine.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>


#define CAST_WIN ( ( GLFWwindow* ) win )


using namespace ege;


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
}


Engine::~Engine()
{
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