
#ifndef EGE_FLOW_ENQUEUEEXECUTOR_HXX
#define EGE_FLOW_ENQUEUEEXECUTOR_HXX

#include <memory>
#include <ege/flow/execution-queue.hxx>
#include <ege/flow/executor.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief An executor that pushes all executables to execute in an specified execution queue.
         *
         * This class is meant to postpone execution of executables.
         * */
        class EnqueueExecutor: public PriorityExecutor
        {
            private:
                /**
                 * \brief Stores the executable passed to execute().
                 * */
                std::shared_ptr<ExecutionQueue> queue;

            public:
                /**
                 * \brief Create the executor with the specified queue where to enqueue Executable objects.
                 * \param queue The specified queue.
                 * */
                EnqueueExecutor(std::shared_ptr<ExecutionQueue> queue);

                virtual ~EnqueueExecutor() {}

                /**
                 * \brief Pushes the specified Executable object in the queue (considering priority).
                 * \param The Executable to push.
                 * \param priority The priority to consider.
                 * */
                virtual void execute(std::shared_ptr<Executable> executable, Priority priority);

                using Executor::execute;
        };
    }
}

#endif
