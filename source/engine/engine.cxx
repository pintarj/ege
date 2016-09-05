#include <ege/engine/engine.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace ege;
using namespace ege::util;


engine::Configuration ege::engine::configuration;
engine::Resources ege::engine::resources;
static GLFWwindow* win;
static uint16_t monitorRefreshRate;


void ege::engine::initialize()
{
        glfwInit();
        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode( primary );
        monitorRefreshRate = ( uint16_t ) videoMode->refreshRate;
        win = glfwCreateWindow( videoMode->width, videoMode->height, "", primary, NULL );
        glfwMakeContextCurrent( win );
        glfwSwapInterval( 1 );
        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();
        resources.monitor = new hardware::Monitor( ( size_t ) videoMode->width, ( size_t ) videoMode->height );
        resources.fpsAnalyzer = new fps::Analyzer();
        resources.fpsModerator = new fps::Moderator( *resources.fpsAnalyzer, ( float ) monitorRefreshRate, true );
        resources.resourcesManager = new resource::Manager( &configuration.root );
}


void ege::engine::start( Scenario* initialScenario )
{
        Scenario* current = initialScenario;
        resources.fpsAnalyzer->markTimePoint();
        resources.fpsAnalyzer->setLastDelta( 1.0f / ( float ) monitorRefreshRate );

        while ( true )
        {
                glfwPollEvents();

                if ( glfwWindowShouldClose( win ) )
                {
                        current->shouldClose();

                        if ( current->isNextScenarioAvailable() )
                                goto should_close_jump;
                }

                current->update( resources.fpsAnalyzer->getLastDelta() );

                if ( current->isNextScenarioAvailable() )
                {
                        should_close_jump:
                        current = current->getNextScenario();

                        if ( current == nullptr )
                                break;
                }

                current->render();
                glfwSwapBuffers( win );
                resources.fpsModerator->moderate();
                resources.fpsAnalyzer->markTimePoint();
        }
}


void ege::engine::destroy()
{
        glfwDestroyWindow( win );
        delete resources.monitor;
        delete resources.fpsAnalyzer;
        delete resources.fpsModerator;
        glfwTerminate();
}
