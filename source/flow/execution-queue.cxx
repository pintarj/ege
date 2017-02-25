#include <ege/flow/execution-queue.hxx>
#include <chrono>
#include <queue>

#define THIS_QUEUE ((std::priority_queue<ExecutionQueueEntry>*) queue)

namespace ege
{
    namespace flow
    {
        class ExecutionQueueEntry
        {
            private:
                std::shared_ptr<Executable> executable;
                Priority priority;
                long timeStamp;

            public:
                ExecutionQueueEntry(const std::shared_ptr<Executable>& executable, Priority priority):
                    executable(executable),
                    priority(priority),
                    timeStamp(std::chrono::steady_clock::now().time_since_epoch().count())
                {

                }

                ~ExecutionQueueEntry()
                {

                }

                bool operator <(const ExecutionQueueEntry& right) const
                {
                    if (this->priority == right.priority)
                        return (this->timeStamp > right.timeStamp);

                    return (this->priority < right.priority);
                }

                std::shared_ptr<Executable> getExecutable() const
                {
                    return executable;
                }
        };

        ExecutionQueue::ExecutionQueue()
        {
            queue = new std::priority_queue<ExecutionQueueEntry>();
        }

        ExecutionQueue::~ExecutionQueue()
        {
            delete THIS_QUEUE;
        }

        void ExecutionQueue::push(std::shared_ptr<Executable> executable, Priority priority)
        {
            THIS_QUEUE->push(ExecutionQueueEntry(executable, priority));
        }

        std::shared_ptr<Executable> ExecutionQueue::pop()
        {
            std::shared_ptr<Executable> executable = THIS_QUEUE->top().getExecutable();
            THIS_QUEUE->pop();
            return executable;
        }

        bool ExecutionQueue::executeOne()
        {
            if (isEmpty())
                return false;

            pop()->execute();
            return true;
        }

        bool ExecutionQueue::isEmpty()
        {
            return THIS_QUEUE->empty();
        }

        SyncExecutionQueue::SyncExecutionQueue():
            pushSignal(mutex, [this]() -> bool
                {
                    return !ExecutionQueue::isEmpty();
                })
        {

        }

        void SyncExecutionQueue::push(std::shared_ptr<Executable> executable, Priority priority, bool notifyAll)
        {
            std::lock_guard<std::mutex> lock(mutex);
            ExecutionQueue::push(executable, priority);

            if (notifyAll)
                pushSignal.getNotifier().notifyAll();
            else
                pushSignal.getNotifier().notifyOne();
        }

        void SyncExecutionQueue::push(std::shared_ptr<Executable> executable, Priority priority)
        {
            push(executable, priority, true);
        }

        std::shared_ptr<Executable> SyncExecutionQueue::pop()
        {
            std::lock_guard<std::mutex> lock(mutex);
            return ExecutionQueue::pop();
        }

        bool SyncExecutionQueue::isEmpty()
        {
            std::lock_guard<std::mutex> lock(mutex);
            return ExecutionQueue::isEmpty();
        }

        SignalWaiter& SyncExecutionQueue::getNotEmptySignalWaiter() const
        {
            return pushSignal.getWaiter();
        }

        bool SyncExecutionQueue::executeOne()
        {
            std::shared_ptr<Executable> executable;

            {
                std::lock_guard<std::mutex> lock(mutex);

                if (ExecutionQueue::isEmpty())
                    return false;

                executable = ExecutionQueue::pop();
            }

            executable->execute();
            return true;
        }
    }
}
