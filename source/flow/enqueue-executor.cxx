#include <ege/flow/enqueue-executor.hxx>

namespace ege
{
    namespace flow
    {
        EnqueueExecutor::EnqueueExecutor(std::shared_ptr<ExecutionQueue> queue):
            queue(queue)
        {

        }

        void EnqueueExecutor::execute(std::shared_ptr<Executable> executable, Priority priority)
        {
            queue->push(executable, priority);
        }
    }
}
