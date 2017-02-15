#include <private/ege/glfw/monitor.hxx>
#include <atomic>
#include <ege/exception.hxx>

namespace ege
{
    namespace glfw
    {
        static std::vector<std::unique_ptr<hardware::Monitor>>  monitors;
        static std::atomic_bool                                 monitorsUpdated(false);

        Monitor::Monitor(const GLFWmonitor* glfwMonitorHandle):
            glfwMonitorHandle(glfwMonitorHandle)
        {
            int                     glfwVideoModesCount     = 0;
            const GLFWvidmode*      glfwVideoModes          = glfwGetVideoModes((GLFWmonitor*) glfwMonitorHandle, &glfwVideoModesCount);
            const GLFWvidmode*      glfwCurrentVideoMode    = glfwGetVideoMode((GLFWmonitor*) glfwMonitorHandle);
            hardware::VideoMode**   videoModes              = new hardware::VideoMode*[glfwVideoModesCount];
            hardware::VideoMode*    currentVideoMode        = nullptr;

            for (unsigned i = 0; i < glfwVideoModesCount; ++i)
            {
                const GLFWvidmode*      glfwVideoMode   = &glfwVideoModes[i];
                int                     width           = glfwVideoMode->width;
                int                     height          = glfwVideoMode->height;
                int                     redBits         = glfwVideoMode->redBits;
                int                     greenBits       = glfwVideoMode->greenBits;
                int                     blueBits        = glfwVideoMode->blueBits;
                int                     refreshRate     = glfwVideoMode->refreshRate;
                hardware::VideoMode*    videoMode       = new hardware::VideoMode(width, height, refreshRate, redBits, greenBits, blueBits, *this);

                if (glfwCurrentVideoMode->width == width &&
                    glfwCurrentVideoMode->height == height &&
                    glfwCurrentVideoMode->redBits == redBits &&
                    glfwCurrentVideoMode->redBits == redBits &&
                    glfwCurrentVideoMode->redBits == redBits &&
                    glfwCurrentVideoMode->redBits == redBits)
                {
                    currentVideoMode = videoMode;
                }

                videoModes[i] = videoMode;
            }

            if (currentVideoMode == nullptr)
                exception::throwNew( "no current video mode found for monitor" );

            this->videoModesCount   = (unsigned) glfwVideoModesCount;
            this->videoModes        = videoModes;
            this->currentVideoMode  = currentVideoMode;
        }

        Monitor::~Monitor()
        {
            for (unsigned int i = 0; i < videoModesCount; ++i)
                delete videoModes[i];

            delete[] videoModes;
        }

        hardware::Monitor::const_iterator Monitor::begin() const
        {
            return videoModes[0];
        }

        hardware::Monitor::const_iterator Monitor::end() const
        {
            return videoModes[videoModesCount];
        }

        const hardware::VideoMode& Monitor::getCurrentVideoMode() const
        {
            return *currentVideoMode;
        }

        const std::vector<std::unique_ptr<hardware::Monitor>>& Monitor::getMonitors()
        {
            if (monitorsUpdated.exchange(true))
                return monitors;

            monitors.clear();
            int count;
            GLFWmonitor** ms = glfwGetMonitors(&count);

            if (ms == nullptr)
                exception::throwNew("no monitors found");

            for (int i = 0; i < count; ++i)
            {
                hardware::Monitor* m = new Monitor(ms[i]);
                monitors.push_back(std::unique_ptr<hardware::Monitor>(m));
            }

            return monitors;
        }
    }
}
