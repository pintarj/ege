#include <ege/flow/executor-thread.hxx>
#include <memory>
#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        ExecutorThread::ExecutorThread(std::shared_ptr<SyncExecutionQueue> queue):
            EnqueueExecutor(queue),
            queue(queue),
            shouldStop(false),
            dismiss(false)
        {

        }

        ExecutorThread::ExecutorThread():
            ExecutorThread(std::shared_ptr<SyncExecutionQueue>(new SyncExecutionQueue))
        {

        }

        void ExecutorThread::execute()
        {
            while (true)
            {
                queue->getNotEmptySignalWaiter().wait(200);

                if (shouldStop && (dismiss || (!dismiss && queue->isEmpty())))
                    break;

                queue->executeOne();
            }
        }

        void ExecutorThread::requireExecutionStop(bool dismiss)
        {
            this->dismiss = dismiss;
            shouldStop = true;
            queue->pushEmptyExecutable(true);
        }

        ExecutorThread::~ExecutorThread()
        {
            requireExecutionStop();
        }
    }
}
