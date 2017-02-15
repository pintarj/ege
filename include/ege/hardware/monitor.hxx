
#ifndef EGE_HARDWARE_MONITOR_HXX
#define EGE_HARDWARE_MONITOR_HXX

namespace ege
{
    namespace hardware
    {
        class Monitor;

        /**
         * \brief The class that describes a particular monitor video mode.
         * */
        struct VideoMode
        {
            public:
                const int width;
                const int height;
                const int redBits;
                const int greenBits;
                const int blueBits;
                const int refreshRate;

                /**
                 * \brief The Monitor that owns this VideoMode.
                 * */
                const Monitor& monitor;

                /**
                 * \brief Create a VideoMode for the specified monitor.
                 * \param width The width of video mode.
                 * \param height The height of video mode.
                 * \param redBits The number of red bits used by video mode.
                 * \param greenBits The number of green bits used by video mode.
                 * \param blueBits The number of blue bits used by video mode.
                 * \param monitor The owner of this video mode.
                 * */
                VideoMode(int width, int height, int refreshRate, int redBits, int greenBits, int blueBits, const Monitor& monitor);
        };

        /**
         * \brief The class that describes properties of a monitor.
         * */
        class Monitor
        {
            public:
                /**
                 * \brief The iterator for video modes associated with \c this Monitor.
                 * */
                typedef const VideoMode* const_iterator;

                virtual ~Monitor() {};

                /**
                 * \brief Returns a pointer to the first VideoMode.
                 * */
                virtual const_iterator begin() const = 0;

                /**
                 * \brief Returns a pointer to one past the last VideoMode.
                 * */
                virtual const_iterator end() const = 0;

                /**
                 * \brief Return the current video mode of \c this monitor.
                 * \return The VideoMode.
                 * */
                virtual const VideoMode& getCurrentVideoMode() const = 0;
        };
    }
}

#endif
