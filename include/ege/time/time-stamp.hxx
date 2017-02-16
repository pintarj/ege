
#ifndef EGE_TIME_TIMESTAMP_HXX
#define EGE_TIME_TIMESTAMP_HXX

#include <chrono>

namespace ege
{
    namespace time
    {
        /**
         * \brief A timestamp in time.
         * \param T Is the type used to represent clock ticks. Default value is "double".
         * \param P Is used to convert the final time. Default is std::ratio<1>.
         * \param C The clock used to calculate times Default is std::chrono::system_clock.
         * */
        template<typename T = double, class P = std::ratio<1>, class C = std::chrono::system_clock>
        class TimeStamp
        {
            private:
                /**
                 * \brief The time point in time.
                 * */
                const std::chrono::time_point<C> timePoint;

            public:
                /**
                 * \brief Create a timestamp in a specific time point.
                 * \param timePoint The specific time point. Default value is C::now() (now).
                 * */
                TimeStamp(std::chrono::time_point<C> timePoint = C::now());

                virtual ~TimeStamp() {}

                /**
                 * \brief Return the elapsed time since the timestamp.
                 * \return The elapsed time.
                 * */
                T getElapsed() const;

                /**
                 * \brief Waits until the time elapsed since the timestamp is equal (or greater) from
                 *      the specified one.
                 * \param elapsed The specified time that have to elapse.
                 * \return The time that has been waited.
                 * */
                T waitUntil(T elapsed) const;
        };
    }
}

#include "time-stamp.txx"

#endif
