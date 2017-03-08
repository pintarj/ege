#include <ege/flow/frame.hxx>

namespace ege
{
    namespace flow
    {
        static Frame::Id nextId = 1;

        Frame::Frame(const TimePoint& timePoint, const TimePoint& prevTimePoint):
            id(nextId++),
            timePoint(timePoint),
            prevTimePoint(prevTimePoint),
            delta(std::chrono::duration<float, std::ratio<1, 1>>(timePoint - prevTimePoint).count())
        {

        }
    }
}
