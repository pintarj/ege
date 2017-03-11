
#ifndef EGE_FLOW_EXECUTORTHREAD_HXX
#define EGE_FLOW_EXECUTORTHREAD_HXX

#include <condition_variable>
#include <memory>
#include <mutex>
#include <ege/flow/enqueue-executor.hxx>
#include <ege/flow/execution-queue.hxx>
#include <ege/flow/thread.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Executes Executable objects on \c this thread.
         *
         * If an Executable is already executing on thread, then all executable that required execution
         * on this thread will be pushed in a queue (considering the priority).
         * */
        class ExecutorThread: public Thread, public EnqueueExecutor
        {
            private:
                /**
                 * \brief The queue where the Executable objects are stored.
                 * */
                std::shared_ptr<SyncExecutionQueue> queue;

                /**
                 * \brief Tells if the thread should stop.
                 * */
                bool shouldStop;

                /**
                 * \brief Tells if when stop is required all the remaining Executable objects have
                 *     to be executed.
                 * */
                bool dismiss;

            protected:
                /**
                 * \brief The executes Executable objects from queue.
                 * */
                virtual void execute() final;

            public:
                /**
                 * \brief Create an executor thread, that uses as queue his own queue.
                 * */
                ExecutorThread();

                /**
                 * \brief Create an executor thread, that uses a specific execution queue.
                 * \param queue The specified execution queue.
                 * */
                ExecutorThread(std::shared_ptr<SyncExecutionQueue> queue);

                /**
                 * \brief During object destruction stop will be required.
                 * \sa requireExecutionStop()
                 * */
                virtual ~ExecutorThread();

                /**
                 * \brief Requires thread execution stop.
                 * \param dismiss Tells if the remaining Executable objects have to be executed.
                 *     \c False will execute the remaining objects, \c true will not.
                 *
                 * The thread will finish to execute the current executing object.
                 * */
                void requireExecutionStop(bool dismiss = false);
        };
    }
}

#endif
