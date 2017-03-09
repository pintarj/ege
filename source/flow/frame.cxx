#include <ege/flow/frame.hxx>
#include <thread>

namespace ege
{
    namespace flow
    {
        static Frame::Id nextId = 1;

        Frame::Frame(const TimePoint& timePoint, const TimePoint& prevTimePoint):
            forwardUpdating(true),
            id(nextId++),
            timePoint(timePoint),
            prevTimePoint(prevTimePoint),
            delta(std::chrono::duration<float, std::ratio<1, 1>>(timePoint - prevTimePoint).count())
        {

        }

        void Frame::waitFuture()
        {
            if (!forwardUpdating)
                return;

            auto now = std::chrono::steady_clock::now();

            if (now < timePoint)
                std::this_thread::sleep_until(timePoint);

            forwardUpdating = false;
        }
    }
}
