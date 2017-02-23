#include <ege/flow/signal.hxx>
#include <chrono>

namespace ege
{
    namespace flow
    {
        class SignalNotifierImplementation: public SignalNotifier
        {
            private:
                std::condition_variable& conditionVariable;
                std::mutex& mutex;

            public:
                SignalNotifierImplementation(std::condition_variable& conditionVariable, std::mutex& mutex);
                virtual ~SignalNotifierImplementation() {}
                virtual void notifyOne();
                virtual void notifyAll();
        };

        class SignalWaiterImplementation: public SignalWaiter
        {
            private:
                std::condition_variable& conditionVariable;
                std::mutex& mutex;

            public:
                SignalWaiterImplementation(std::condition_variable& conditionVariable, std::mutex& mutex);
                virtual ~SignalWaiterImplementation() {}
                virtual void wait();
                virtual void wait(long milliseconds, int nanoseconds);
        };

        class SignalWaiterPredicateImplementation: public SignalWaiter
        {
            private:
                std::condition_variable& conditionVariable;
                std::mutex& mutex;
                const std::function<bool()> predicate;

            public:
                SignalWaiterPredicateImplementation(std::condition_variable& conditionVariable, std::mutex& mutex,
                    const std::function<bool()>& predicate);

                virtual ~SignalWaiterPredicateImplementation() {}
                virtual void wait();
                virtual void wait(long milliseconds, int nanoseconds);
        };

        SignalNotifierImplementation::SignalNotifierImplementation(std::condition_variable& conditionVariable,
                std::mutex& mutex):
            conditionVariable(conditionVariable),
            mutex(mutex)
        {

        }

        void SignalNotifierImplementation::notifyOne()
        {
            std::lock_guard<std::mutex> lock(mutex);
            conditionVariable.notify_one();
        }

        void SignalNotifierImplementation::notifyAll()
        {
            std::lock_guard<std::mutex> lock(mutex);
            conditionVariable.notify_all();
        }

        SignalWaiterImplementation::SignalWaiterImplementation(std::condition_variable& conditionVariable,
                std::mutex& mutex):
            conditionVariable(conditionVariable),
            mutex(mutex)
        {

        }

        void SignalWaiterImplementation::wait()
        {
            std::unique_lock<std::mutex> lock(mutex);
            conditionVariable.wait(lock);
        }

        void SignalWaiterImplementation::wait(long milliseconds, int nanoseconds)
        {
            std::unique_lock<std::mutex> lock(mutex);
            auto duration = std::chrono::milliseconds(milliseconds) + std::chrono::nanoseconds(nanoseconds);
            conditionVariable.wait_for(lock, duration);
        }

        SignalWaiterPredicateImplementation::SignalWaiterPredicateImplementation(
                std::condition_variable& conditionVariable, std::mutex& mutex, const std::function<bool()>& predicate):
            conditionVariable(conditionVariable),
            mutex(mutex),
            predicate(predicate)
        {

        }

        void SignalWaiterPredicateImplementation::wait()
        {
            std::unique_lock<std::mutex> lock(mutex);
            conditionVariable.wait(lock, predicate);
        }

        void SignalWaiterPredicateImplementation::wait(long milliseconds, int nanoseconds)
        {
            std::unique_lock<std::mutex> lock(mutex);
            auto duration = std::chrono::milliseconds(milliseconds) + std::chrono::nanoseconds(nanoseconds);
            conditionVariable.wait_for(lock, duration, predicate);
        }

        Signal::Signal(std::mutex& mutex):
            notifier(new SignalNotifierImplementation(conditionVariable, mutex)),
            waiter(new SignalWaiterImplementation(conditionVariable, mutex)),
            mutex(mutex)
        {

        }

        Signal::Signal(std::mutex& mutex, const std::function<bool()>& predicate):
            notifier(new SignalNotifierImplementation(conditionVariable, mutex)),
            waiter(new SignalWaiterPredicateImplementation(conditionVariable, mutex, predicate)),
            mutex(mutex)
        {

        }

        SignalNotifier& Signal::getNotifier() const
        {
            return *notifier;
        }

        SignalWaiter& Signal::getWaiter() const
        {
            return *waiter;
        }
    }
}
