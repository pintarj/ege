#include <ege/flow/executor-thread.hxx>
#include <memory>
#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        ExecutorThread::ExecutorThread():
            shouldStop(false),
            waiting(false),
            dismiss(false)
        {

        }

        void ExecutorThread::execute(std::shared_ptr<Executable> executable, Priority priority)
        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(executable, priority);

            if (waiting)
                wakeUp.notify_one();
        }

        void ExecutorThread::execute()
        {
            while (true)
            {
                std::shared_ptr<Executable> executable;

                {
                    std::unique_lock<std::mutex> lock(mutex);

                    waiting = true;
                    wakeUp.wait(lock, [this]() -> bool { return !queue.isEmpty() || shouldStop; });
                    waiting = false;

                    if (shouldStop && (dismiss || (!dismiss && queue.isEmpty())))
                        break;

                    executable = queue.pop();
                }

                executable->execute();
            }
        }

        void ExecutorThread::requireExecutionStop(bool dismiss)
        {
            std::lock_guard<std::mutex> lock(mutex);
            this->dismiss = dismiss;
            shouldStop = true;

            if (waiting)
                wakeUp.notify_one();
        }

        ExecutorThread::~ExecutorThread()
        {
            requireExecutionStop();
        }
    }
}
