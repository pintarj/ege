
#ifndef EGE_FLOW_SIGNAL_HXX
#define EGE_FLOW_SIGNAL_HXX

#include <condition_variable>
#include <functional>
#include <mutex>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Meant for wake up waiting threads (signaling them).
         *
         * Certain implementations may produce spurious wake-up calls (signal) without any call of
         * Signal::notifyOne() or Signal::notifyAll(). So, a predicate should be specified, to check
         * those type of events.
         * */
        class Signal
        {
            private:
                /**
                 * \brief The signal's conditional variable. Used to wait and notify.
                 * */
                std::condition_variable conditionVariable;

                /**
                 * \brief Used to synchronize access to conditional variable.
                 * */
                std::mutex mutex;

                /**
                 * \brief Used to check spurious wake-up calls (if specified).
                 * */
                const std::function<bool()> predicate;

                /**
                 * \brief Tells if a predicate has been specified in constructor.
                 * */
                const bool predicateSpecified;

            public:
                /**
                 * \brief Create a Signal object without a predicate.
                 * */
                Signal();

                /**
                 * \brief Create a Signal object that will use a specific predicate to check spurious wake ups.
                 * \param predicate Used to check spurious wake-up calls.
                 * */
                Signal(const std::function<bool()>& predicate);

                /**
                 * \brief Current thread waits to be signaled (notified).
                 * \sa notifyOne()
                 * \sa notifyAll()
                 *
                 * Thread can be signaled by some other thread.
                 * */
                void wait();

                /**
                 * \brief Current thread waits, for an amount of time, to be signaled (notified).
                 * \param milliseconds Milliseconds to wait.
                 * \param nanoseconds Nanoseconds to wait.
                 * \sa notifyOne()
                 * \sa notifyAll()
                 *
                 * The waiting time is the sum of milliseconds and nanoseconds. \n
                 * Thread can be signaled by some other thread.
                 * */
                void wait(long milliseconds, int nanoseconds = 0);

                /**
                 * \brief Wakes up a single thread that is waiting on \c this signal.
                 * \sa wait()
                 * */
                void notifyOne();

                /**
                 * \brief Wakes up all the threads that are waiting on \c this signal.
                 * \sa wait()
                 * */
                void notifyAll();
        };
    }
}

#endif
