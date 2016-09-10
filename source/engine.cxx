#include <ege/engine.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace ege;
using namespace ege::scenario;
using namespace ege::util;


class EgeKeyboard: public hardware::Keyboard
{
        private:
                GLFWwindow* win;

        public:
                EgeKeyboard( GLFWwindow* win )
                {
                        this->win = win;
                }

                bool isPressed( hardware::KeyboardKey key )
                {
                        return glfwGetKey( win, ( int ) key ) == GLFW_PRESS;
                }
};


engine::Resources ege::engine::resources;


void engine::start( const std::function< void( engine::Configurations& ) >& configure )
{
        glfwInit();
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode( primary );
        uint16_t monitorRefreshRate = ( uint16_t ) videoMode->refreshRate;
        glfwDefaultWindowHints();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
        GLFWwindow* win = glfwCreateWindow( videoMode->width, videoMode->height, "", primary, NULL );
        glfwMakeContextCurrent( win );
        glfwSwapInterval( 1 );

        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();

        engine::resources.keyboard = new EgeKeyboard( win );
        engine::resources.monitor = new hardware::Monitor( ( size_t ) videoMode->width, ( size_t ) videoMode->height );
        engine::resources.fpsAnalyzer = new fps::Analyzer();
        engine::resources.fpsModerator = new fps::Moderator( *engine::resources.fpsAnalyzer, ( float ) monitorRefreshRate, true );

        engine::Configurations* configurations = new engine::Configurations;
        configure( *configurations );
        Scenario* current = configurations->initialScenario;
        delete configurations;

        resources.fpsAnalyzer->calculateDeltaAndMark();
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
                resources.fpsAnalyzer->calculateDeltaAndMark();
        }

        glfwDestroyWindow( win );
        delete engine::resources.keyboard;
        delete engine::resources.monitor;
        delete engine::resources.fpsAnalyzer;
        delete engine::resources.fpsModerator;
        glfwTerminate();
}
