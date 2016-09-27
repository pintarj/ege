#include <ege/hardware/keyboard.hxx>
#include <ege/exception.hxx>
#include <GLFW/glfw3.h>
#include <cstring>
#include <atomic>
#include <set>


using namespace ege;
using namespace ege::hardware;


namespace global
{
        static std::atomic_bool keyboardInstanced;
        static bool keysPressed[ 350 ];
        static std::set< keyboard::key::EventListener* > listeners;
}


void keyboard::key::EventListener::onKeyPress( Key key, Modifier modifier )
{

}


void keyboard::key::EventListener::onKeyRelease( Key key, Modifier modifier )
{

}


void Keyboard::listenOnWindows( void** windows, unsigned int count )
{
        std::memset( global::keysPressed, 0, sizeof( global::keysPressed ) );

        for ( unsigned int i = 0; i < count; ++i )
        {
                glfwSetKeyCallback( static_cast< GLFWwindow* >( windows[ i ] ), [] ( GLFWwindow* window, int key, int scanCode, int action, int modifier )
                {
                        switch ( action )
                        {
                                case GLFW_PRESS:
                                {
                                        global::keysPressed[ key ] = true;

                                        for ( keyboard::key::EventListener* listener : global::listeners )
                                                listener->onKeyPress( ( keyboard::Key ) key, keyboard::key::Modifier( modifier ) );

                                        break;
                                }

                                case GLFW_RELEASE:
                                {
                                        global::keysPressed[ key ] = false;

                                        for ( keyboard::key::EventListener* listener : global::listeners )
                                                listener->onKeyRelease( ( keyboard::Key ) key, keyboard::key::Modifier( modifier ) );

                                        break;
                                }

                                default:
                                        break;
                        }
                } );
        }
}


Keyboard::Keyboard()
{
        if ( global::keyboardInstanced.exchange( true ) )
                Exception::throwNew( "could not create second interface to keyboard" );

        std::memset( global::keysPressed, 0, sizeof( global::keysPressed ) );
}


Keyboard::~Keyboard()
{
        global::listeners.clear();
        global::keyboardInstanced = false;
}


bool Keyboard::isPressed( keyboard::Key key ) const
{
        return global::keysPressed[ ( size_t ) key ];
}


void Keyboard::addKeyEventListener( keyboard::key::EventListener* listener )
{
        global::listeners.insert( listener );
}


void Keyboard::removeKeyEventListener( keyboard::key::EventListener* listener )
{
        global::listeners.erase( listener );
}
