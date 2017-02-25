
#ifndef PRIVATE_EGE_ENGINE_RESOURCES_HXX
#define PRIVATE_EGE_ENGINE_RESOURCES_HXX

#include <memory>
#include <ege/engine/configuration.hxx>
#include <ege/flow/execution-queue.hxx>
#include <ege/flow/scene.hxx>
#include <private/ege/engine/control-thread.hxx>
#include <private/ege/glfw/window.hxx>

namespace ege
{
    namespace engine
    {
        /**
         * \brief Initialize and configure engine resources.
         * \param configuration The configuration specified by user.
         * */
        void initializeAndConfigure(Configuration& configuration);

        /**
         * \brief Destroy the engine resources.
         * */
        void destroy();

        /**
         * \brief Returns the GLFW window created by engine.
         * \return The window.
         * */
        glfw::Window& getGLFWWindow();

        /**
         * \brief Returns the graphic execution queue.
         * \return The graphic execution queue.
         * */
        flow::SyncExecutionQueue& getGraphicExecutionQueue();

        /**
         * \brief Returns the engine control thread.
         * \return The engine control thread.
         * */
        engine::ControlThread& getControlThread();
    }
}

#endif
