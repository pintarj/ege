#include <ege/hardware/monitor.hxx>

namespace ege
{
    namespace hardware
    {
        VideoMode::VideoMode(int width, int height, int refreshRate, int redBits, int greenBits, int blueBits, const Monitor& monitor):
            width(width),
            height(height),
            refreshRate(refreshRate),
            redBits(redBits),
            greenBits(greenBits),
            blueBits(blueBits),
            monitor(monitor)
        {

        }
    }
}
