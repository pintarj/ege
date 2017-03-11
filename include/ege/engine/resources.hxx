
#ifndef EGE_ENGINE_RESOURCES_HXX
#define EGE_ENGINE_RESOURCES_HXX

#include <memory>
#include <vector>
#include <ege/log.hxx>
#include <ege/keyboard.hxx>
#include <ege/flow/executor.hxx>
#include <ege/flow/fragment.hxx>
#include <ege/flow/parallel-nucleus.hxx>
#include <ege/hardware/monitor.hxx>
#include <ege/opengl/context.hxx>

namespace ege
{
    namespace engine
    {
        /**
         * \brief Returns the engine Logger.
         * \return The engine Logger.
         *
         * The engine logger is always available (even is engine is not started).
         * */
        log::Logger& getLogger();

        /**
         * \brief Returns a vector of connected monitors.
         * \return The vector.
         *
         * The monitor vector is available during engine execution (also at configuration).
         * */
        const std::vector<std::unique_ptr<hardware::Monitor>>& getMonitors();

        /**
         * \brief Returns the primary monitor.
         * \return The primary monitor.
         *
         * The primary monitor can be found also in vector returned by getMonitors() at index 0. \n
         * The monitor vector is available during engine execution (also at configuration).
         * */
        hardware::Monitor& getPrimaryMonitor();

        /**
         * \brief Returns the engine OpenGL context.
         * \return The engine OpenGL context.
         *
         * The engine OpenGL context is available AFTER engine configuration.
         * */
        opengl::Context& getOpenglContext();

        /**
         * \brief Returns the engine graphic Executor.
         * \return The engine graphic Executor.
         *
         * The engine graphic Executor is available during engine execution (also at configuration).
         * */
        flow::PriorityExecutor& getGraphicExecutor();

        /**
         * \brief Returns an interface to the connected keyboard.
         * \return The interface to the connected keyboard.
         *
         * The interface to connected keyboard is available AFTER engine configuration.
         * */
        keyboard::Keyboard& getKeyboard();

        /**
         * \brief Returns the event update fragment.
         * \return The event update Fragment.
         *
         * The interface to connected keyboard is available AFTER engine configuration.
         * */
        std::shared_ptr<flow::Fragment> getEventUpdateFragment();

        /**
         * \brief Returns the parallel nucleus.
         * \return The parallel nucleus.
         *
         * The engine graphic Executor is available during engine execution (also at configuration).
         * */
        flow::ParallelNucleus& getParallelNucleus();
    }
}

#endif
