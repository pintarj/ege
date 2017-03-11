
#ifndef EGE_FLOW_PARALLELNUCLEUS_HXX
#define EGE_FLOW_PARALLELNUCLEUS_HXX

#include <memory>
#include <thread>
#include <ege/flow/enqueue-executor.hxx>
#include <ege/flow/executor-thread.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Execute Executable objects in parallel.
         * */
        class ParallelNucleus: public EnqueueExecutor
        {
            private:
                /**
                 * \brief The queue where are stored Executable objects, that can't be currently executed,
                 *     because all threads are busy.
                 * */
                std::shared_ptr<SyncExecutionQueue> queue;

                /**
                 * \param Stores the number of threads that \c this nucleus uses.
                 * */
                unsigned numberOfThreads;

                /**
                 * \brief Here are stored the threads that are executing objects from queue.
                 * */
                ExecutorThread** threads;

                /**
                 * \brief Create an ParallelNucleus, that works with the specified number of threads and
                 *     executing objects from a specified queue.
                 * \param numberOfThread The number of thread used by nucleus. Default is the number of CPU cores.
                 * \param queue The queue from which the objects will be executed.
                 * */
                ParallelNucleus(std::shared_ptr<SyncExecutionQueue> queue, unsigned numberOfThreads);

            public:
                /**
                 * \brief Create an ParallelNucleus, that works with the specified number of threads.
                 * \param numberOfThread The number of thread used by nucleus. Default is the number of CPU cores.
                 * */
                ParallelNucleus(unsigned numberOfThreads = std::thread::hardware_concurrency());

                /**
                 * \brief Execute all content of queue and then stop and join the threads.
                 *
                 * Note that this operation can require a considerable amount of time depending of
                 * what is remaining inside the queue.
                 * */
                virtual ~ParallelNucleus();
        };
    }
}

#endif
