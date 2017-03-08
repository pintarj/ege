
#ifndef EGE_FLOW_FRAME_HXX
#define EGE_FLOW_FRAME_HXX

#include <chrono>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Represent a single frame.
         * */
        class Frame
        {
            public:

                /**
                 * \brief The frame id type.
                 * */
                typedef unsigned long long Id;

                /**
                 * \brief The time point type.
                 * */
                typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

                /**
                 * \brief The id of the frame.
                 * */
                const Id id;

                /**
                 * \brief The time point of the previously updating frame.
                 * \sa delta
                 *
                 * Stored for measuring delta (different from float type, with ratio representing seconds). \n
                 * Note that the time point is measured using std::chrono::steady_clock, so
                 * the time stored could not represent the current wall time.
                 * */
                const TimePoint prevTimePoint;

                /**
                 * \brief The time point of the updating frame.
                 *
                 * The value is stored for 2 purposes:
                 *  - uniform update time point for all object's update
                 *  - avoid multiple system calls caused by multiple fetch of time
                 *
                 * Note that the time point is measured using std::chrono::steady_clock, so
                 * the time stored could not represent the current wall time.
                 * */
                const TimePoint timePoint;

                /**
                 * \brief The time that the frame is going to update (the time passed since
                 *     the last frame was rendered).
                 *
                 * The time is stored in seconds. \n
                 * It's simply calculated subtracting prevTimePoint from timePoint.
                 * */
                const float delta;

                /**
                 * \brief Create a frame representation at the specified time point.
                 * \param timePoint The specified time point.
                 * */
                Frame(const TimePoint& timePoint, const TimePoint& prevTimePoint);

                virtual ~Frame() {}
        };
    }
}

#endif
