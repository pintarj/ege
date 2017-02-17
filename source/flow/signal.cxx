#include <ege/flow/signal.hxx>
#include <chrono>

namespace ege
{
    namespace flow
    {
        Signal::Signal():
            predicate([]() -> bool {return true;}),
            predicateSpecified(false)
        {

        }

        Signal::Signal(const std::function<bool()>& predicate):
            predicate(predicate),
            predicateSpecified(true)
        {

        }

        void Signal::wait()
        {
            std::unique_lock<std::mutex> lock(mutex);

            if (predicateSpecified)
                conditionVariable.wait(lock, predicate);
            else
                conditionVariable.wait(lock);
        }

        void Signal::wait(long milliseconds, int nanoseconds)
        {
            std::unique_lock<std::mutex> lock(mutex);
            auto duration = std::chrono::milliseconds(milliseconds) + std::chrono::nanoseconds(nanoseconds);

            if (predicateSpecified)
                conditionVariable.wait_for(lock, duration, predicate);
            else
                conditionVariable.wait_for(lock, duration);
        }

        void Signal::notifyOne()
        {
            std::lock_guard<std::mutex> lock(mutex);
            conditionVariable.notify_one();
        }

        void Signal::notifyAll()
        {
            std::lock_guard<std::mutex> lock(mutex);
            conditionVariable.notify_all();
        }
    }
}
