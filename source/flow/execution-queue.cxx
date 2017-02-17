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
                ExecutionPriority priority;
                long timeStamp;

            public:
                ExecutionQueueEntry(const std::shared_ptr<Executable>& executable, ExecutionPriority priority):
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

        void ExecutionQueue::push(std::shared_ptr<Executable> executable, ExecutionPriority priority)
        {
            std::unique_lock<std::mutex> lock(mutex);
            THIS_QUEUE->push(ExecutionQueueEntry(executable, priority));
        }

        std::shared_ptr<Executable> ExecutionQueue::pop()
        {
            std::unique_lock<std::mutex> lock(mutex);
            std::shared_ptr<Executable> executable = THIS_QUEUE->top().getExecutable();
            THIS_QUEUE->pop();
            return executable;
        }

        void ExecutionQueue::execute()
        {
            pop()->execute();
        }

        bool ExecutionQueue::isEmpty()
        {
            std::unique_lock<std::mutex> lock(mutex);
            return THIS_QUEUE->empty();
        }
    }
}
