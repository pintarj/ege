
#ifndef EGE_FLOW_EXECUTIONQUEUE_HXX
#define EGE_FLOW_EXECUTIONQUEUE_HXX

#include <memory>
#include <mutex>
#include <ege/flow/executable.hxx>
#include <ege/flow/priority.hxx>
#include <ege/flow/signal.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Represent an execution queue of Executable objects.
         *
         * Executable objects can be pushed in the queue and popped from the queue. Executables are executed
         * by priority: higher priority is firstly executed. Executables of equal priority are executed in
         * order they are pushed in the queue.
         * */
        class ExecutionQueue
        {
            private:
                /**
                 * \brief The priority queue where executables are stored.
                 * */
                void* queue;

            public:
                /**
                 * \brief Create an empty execution queue.
                 * */
                ExecutionQueue();

                virtual ~ExecutionQueue();

                /**
                 * \brief Push an Executable object to the queue.
                 * \param executable The executable object to push.
                 * \param priority The priority of object execution. Default is Priority::DEFAULT.
                 * */
                virtual void push(std::shared_ptr<Executable> executable, Priority priority = Priority::DEFAULT);

                /**
                 * \brief Pop the Executable object at the top of the queue.
                 * \return The popped Executable.
                 * */
                virtual std::shared_ptr<Executable> pop();

                /**
                 * \brief Tells if queue is empty.
                 * \return \c True if queue is empty, false otherwise.
                 * */
                virtual bool isEmpty();

                /**
                 * \brief Execute one Executable object from the queue (if it's not empty).
                 * \return \c True if the queue was not empty and an Executable was executed, \c false otherwise.
                 *
                 * Implementation: \n
                 * \code
                 * if (isEmpty())
                 *     return false;
                 *
                 * pop()->execute();
                 * return true;
                 * \endcode
                 * */
                virtual bool executeOne();
        };

        /**
         * \brief Represent a synchronized execution queue of Executable objects.
         *
         * Executable objects can be pushed in the queue and popped from the queue. Executables are executed
         * by priority: higher priority is firstly executed. Executables of equal priority are executed in
         * order they are pushed in the queue. \n
         * \n
         * Methods of this class are thread-safe. \n
         * \n
         * Each queue has an associated signal, that will be notified when an executable is added to the queue.
         * */
        class SyncExecutionQueue: public ExecutionQueue
        {
            private:
                /**
                 * \brief Signal used to communicate to other threads that the queue is not empty.
                 * */
                Signal pushSignal;

            public:
                /**
                 * \brief Mutex used by methods of this class to synchronize access to the queue.
                 * */
                std::mutex mutex;

                /**
                 * \brief Create an empty execution queue.
                 * */
                SyncExecutionQueue();

                virtual ~SyncExecutionQueue() {}

                /**
                 * \brief Push an Executable object to the queue.
                 * \param executable The executable object to push.
                 * \param priority The priority of object execution.
                 * \param notifyAll If \c true, all the waiting threads will be notified (Signal::notifyAll()),
                 *     otherwise only one (Signal::notifyOne()).
                 *
                 * This method will notify all waiting threads using associated signal. \n
                 * The method is synchronized using SyncExecutionQueue::mutex.
                 * */
                virtual void push(std::shared_ptr<Executable> executable, Priority priority, bool notifyAll);

                /**
                 * \brief Call method push(std::shared_ptr<Executable>, Priority, bool) forwarding executable
                 *     and priority and passing true as \c notifyAll.
                 * \param executable The executable object to forward.
                 * \param priority The priority to forward. Default is Priority::DEFAULT.
                 * */
                virtual void push(std::shared_ptr<Executable> executable, Priority priority = Priority::DEFAULT) override;

                /**
                 * \brief Pop the Executable object at the top of the queue.
                 * \return The popped Executable.
                 *
                 * The method is synchronized using SyncExecutionQueue::mutex.
                 * */
                virtual std::shared_ptr<Executable> pop() override;

                /**
                 * \brief Tells if queue is empty.
                 * \return \c True if queue is empty, false otherwise.
                 *
                 * The method is synchronized using SyncExecutionQueue::mutex.
                 * */
                virtual bool isEmpty() override;

                /**
                 * \brief Return the signal waiter, that will be notified when an executable is added to the queue.
                 * \return The signal queue.
                 * */
                SignalWaiter& getNotEmptySignalWaiter() const;

                /**
                 * \brief Execute one Executable object from the queue (if it's not empty).
                 * \return \c True if the queue was not empty and an Executable was executed, \c false otherwise.
                 *
                 * The method is synchronized using SyncExecutionQueue::mutex, (the execution is not synchronized). \n
                 * Logic implementation (note that in reality the access is synchronized): \n
                 * \code
                 * if (isEmpty())
                 *     return false;
                 *
                 * pop()->execute();
                 * return true;
                 * \endcode
                 * */
                virtual bool executeOne() override;
        };
    }
}

#endif
