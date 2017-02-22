
#ifndef EGE_FLOW_EXECUTORTHREAD_HXX
#define EGE_FLOW_EXECUTORTHREAD_HXX

#include <condition_variable>
#include <mutex>
#include <ege/flow/execution-queue.hxx>
#include <ege/flow/executor.hxx>
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
        class ExecutorThread: public PriorityExecutor, public Thread
        {
            private:
                /**
                 * \brief The queue where the Executable objects are stored.
                 * */
                ExecutionQueue queue;

                /**
                 * \brief The mutex used to synchronize operations.
                 * */
                std::mutex mutex;

                /**
                 * \brief Variable used to wake up executor thread.
                 * */
                std::condition_variable wakeUp;

                /**
                 * \brief Tells if the thread should stop.
                 * */
                bool shouldStop;

                /**
                 * \brief Tells if the thread is currently waiting some executable to execute.
                 * */
                bool waiting;

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
                 * \brief Create an executor thread.
                 * */
                ExecutorThread();

                /**
                 * \brief During object destruction stop will be required.
                 * \sa requireExecutionStop()
                 * */
                virtual ~ExecutorThread();

                /**
                 * \brief Execute the Executable on the thread considering the execution priority.
                 * \param executable The Executable to execute on thread.
                 * \param priority The execution priority to consider.
                 * */
                virtual void execute(std::shared_ptr<Executable> executable, Priority priority) override;

                using PriorityExecutor::execute;

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
