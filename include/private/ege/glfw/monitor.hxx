
#ifndef EGE_GLFW_MONITOR_HXX
#define EGE_GLFW_MONITOR_HXX

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include <ege/hardware/monitor.hxx>

namespace ege
{
    namespace glfw
    {
        /**
         * \brief An implementation of hardware::Monitor using GLFW.
         * */
        class Monitor: public hardware::Monitor
        {
            private:
                /**
                 * \brief The video modes available for \c this Monitor.
                 * */
                hardware::VideoMode** videoModes;

                /**
                 * \brief The number of video modes available for \c this Monitor.
                 * */
                unsigned videoModesCount;

                /**
                 * \brief The current video mode for \c this Monitor.
                 * */
                hardware::VideoMode* currentVideoMode;

                /**
                 * \brief Create the monitor wrapper given the GLFW monitor handle.
                 * \param glfwMonitorHandle The GLFW monitor handle.
                 * */
                Monitor(const GLFWmonitor* glfwMonitorHandle);

            public:
                /**
                 * \brief The GLFW monitor handle.
                 * */
                const GLFWmonitor* const glfwMonitorHandle;

                virtual ~Monitor();

                /**
                 * \brief Returns a pointer to the first VideoMode.
                 * */
                virtual hardware::Monitor::const_iterator begin() const;

                /**
                 * \brief Returns a pointer to one past the last VideoMode.
                 * */
                virtual hardware::Monitor::const_iterator end() const;

                /**
                 * \brief Return the current video mode of \c this monitor.
                 * \return The VideoMode.
                 * */
                virtual const hardware::VideoMode& getCurrentVideoMode() const;

                /**
                 * \brief Return the reference to a vector containing all current connected monitors.
                 * \return The vector containing monitors.
                 *
                 * The primary monitor is at index 0.
                 * */
                static const std::vector<std::unique_ptr<hardware::Monitor>>& getMonitors();
        };
    }
}

#endif
