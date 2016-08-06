#include <ege/engine/engine.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>


using namespace ege;


class DefaultCanvas: public ege::graphic::Canvas
{
        public:
                DefaultCanvas( size_t width, size_t height ): Canvas( true, width, height )
                {

                }

                ~DefaultCanvas() {}
};


engine::Configuration ege::engine::configuration;
engine::Resources ege::engine::resources;
static GLFWwindow* win;


void ege::engine::initialize()
{
        glfwInit();
        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode( primary );
        win = glfwCreateWindow( videoMode->width, videoMode->height, "", primary, NULL );
        glfwMakeContextCurrent( win );
        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();
        resources.screen = new DefaultCanvas( ( size_t ) videoMode->width, ( size_t ) videoMode->height );
        resources.resourcesManager = new resource::Manager( &configuration.root );
}


void ege::engine::start( Scenario* initialScenario )
{
        Scenario* current = initialScenario;

        while ( true )
        {
                glfwPollEvents();

                if ( glfwWindowShouldClose( win ) )
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

                glfwSwapBuffers( win );
                std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
        }
}


void ege::engine::destroy()
{
        glfwDestroyWindow( win );
        delete resources.screen;
        glfwTerminate();
}
