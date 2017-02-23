
#ifndef EGE_FLOW_SIGNAL_HXX
#define EGE_FLOW_SIGNAL_HXX

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Class that allow notification of threads waiting to be notified.
         * */
        class SignalNotifier
        {
            public:
                virtual ~SignalNotifier() {}

                /**
                 * \brief Wakes up a single thread that is waiting on \c this signal.
                 * \sa wait()
                 * */
                virtual void notifyOne() = 0;

                /**
                 * \brief Wakes up all the threads that are waiting on \c this signal.
                 * \sa wait()
                 * */
                virtual void notifyAll() = 0;
        };

        /**
         * \brief Class that allow executing thread waits to be notified by other thread.
         * */
        class SignalWaiter
        {
            public:
                virtual ~SignalWaiter() {}

                /**
                 * \brief Current thread waits to be signaled (notified).
                 * \sa SignalNotifier::notifyOne()
                 * \sa SignalNotifier::notifyAll()
                 *
                 * Thread can be signaled by some other thread.
                 * */
                virtual void wait() = 0;

                /**
                 * \brief Current thread waits, for an amount of time, to be signaled (notified).
                 * \param milliseconds Milliseconds to wait.
                 * \param nanoseconds Nanoseconds to wait.
                 * \sa SignalNotifier::notifyOne()
                 * \sa SignalNotifier::notifyAll()
                 *
                 * The waiting time is the sum of milliseconds and nanoseconds. \n
                 * Thread can be signaled by some other thread.
                 * */
                virtual void wait(long milliseconds, int nanoseconds = 0) = 0;
        };

        /**
         * \brief Meant for signaling threads between them.
         *
         * Certain implementations may produce spurious wake-up calls (signal) without any call of
         * SignalNotifier::notifyOne() or SignalNotifier::notifyAll(). So, a predicate should be specified,
         * to check those type of events. \n
         * When a predicate is specified the wait methods will act as follow.
         * \code
         * while (!predicate())
         *     wait(lock);
         * \endcode
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
                std::mutex& mutex;

                /**
                 * \brief The object that notifies signals.
                 * */
                std::unique_ptr<SignalNotifier> notifier;

                /**
                 * \brief The object that waits for signal notifications.
                 * */
                std::unique_ptr<SignalWaiter> waiter;

            public:

                /**
                 * \brief Create a Signal object that will use a specific predicate to check spurious wake ups.
                 * \param predicate Used to check spurious wake-up calls.
                 * \param mutex The mutex used to synchronize signals.
                 * */
                Signal(std::mutex& mutex, const std::function<bool()>& predicate);

                /**
                 * \brief Create a Signal object without a predicate, that is synchronized using specified mutex.
                 * \param mutex The mutex used to synchronize signals.
                 * */
                Signal(std::mutex& mutex);

                /**
                 * \brief Gets the signal's notifier.
                 * \return The signal notifier.
                 * */
                SignalNotifier& getNotifier() const;

                /**
                 * \brief Gets the signal's waiter.
                 * \return The signal waiter.
                 * */
                SignalWaiter& getWaiter() const;
        };
    }
}

#endif
