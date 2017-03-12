
#ifndef PRIVATE_EGE_ENGINE_RESOURCES_HXX
#define PRIVATE_EGE_ENGINE_RESOURCES_HXX

#include <memory>
#include <ege/engine/configuration.hxx>
#include <ege/flow/execution-queue.hxx>
#include <ege/flow/fps-analyzer.hxx>
#include <ege/flow/scene.hxx>
#include <private/ege/engine/control-thread.hxx>
#include <private/ege/flow/origin-fragment.hxx>
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

        /**
         * \brief Returns the origin fragment.
         * \return The origin fragment.
         * */
        flow::OriginFragment& getOriginFragment();

        /**
         * \brief Returns the FPS analyzer (non-const reference).
         * \return The FPS analyzer (non-const reference).
         * */
        flow::FPSAnalyzer& getNonConstFPSAnalyzer();
    }
}

#endif
