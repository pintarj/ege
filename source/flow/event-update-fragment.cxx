#include <private/ege/flow/event-update-fragment.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <private/ege/engine/resources.hxx>

namespace ege
{
    namespace flow
    {
        EventUpdateFragment::EventUpdateFragment()
        {

        }

        void EventUpdateFragment::performUpdate(const Frame& frame)
        {
            glfwPollEvents();
            glfwPollEvents(); // solve bug: glfw perform a key repressed after key repeating

            if (engine::getGLFWWindow().shouldClose())
                engine::getControlThread().getCurrentScene().shouldClose();
        }
    }
}
