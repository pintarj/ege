#include <ege/flow/parallel-nucleus.hxx>

namespace ege
{
    namespace flow
    {
        ParallelNucleus::ParallelNucleus(std::shared_ptr<SyncExecutionQueue> queue, unsigned numberOfThreads):
            EnqueueExecutor(queue),
            queue(queue),
            numberOfThreads(numberOfThreads),
            threads([queue, numberOfThreads]() -> ExecutorThread**
                {
                    ExecutorThread** array = new ExecutorThread*[numberOfThreads];

                    for (unsigned i = 0; i < numberOfThreads; ++i)
                        array[i] = new ExecutorThread(queue);

                    return array;
                } ())
        {
            for (unsigned i = 0; i < numberOfThreads; ++i)
                threads[i]->start();
        }

        ParallelNucleus::ParallelNucleus(unsigned numberOfThreads):
            ParallelNucleus(std::shared_ptr<SyncExecutionQueue>(new SyncExecutionQueue), numberOfThreads)
        {

        }

        ParallelNucleus::~ParallelNucleus()
        {
            for (unsigned i = 0; i < numberOfThreads; ++i)
                threads[i]->requireExecutionStop(false);

            for (unsigned i = 0; i < numberOfThreads; ++i)
            {
                threads[i]->join();
                delete threads[i];
            }

            delete threads;
        }
    }
}
