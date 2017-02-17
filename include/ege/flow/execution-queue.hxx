
#ifndef EGE_FLOW_EXECUTIONQUEUE_HXX
#define EGE_FLOW_EXECUTIONQUEUE_HXX

#include <memory>
#include <mutex>
#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Enumerate execution priorities.
         *
         * Default is MEDIUM.
         * */
        enum class ExecutionPriority: unsigned int
        {
            EXTREME = 4,
            HIGH    = 3,
            MEDIUM  = 2,
            LOW     = 1,
            ZERO    = 0,
            DEFAULT = MEDIUM
        };

        /**
         * \brief Represent an execution queue of Executable objects.
         *
         * Executable objects can be pushed in the queue and popped from the queue. Executables are executed
         * by priority: higher priority is firstly executed. Executables of equal priority are executed in
         * order they are pushed in the queue. \n
         * \n
         * Implementation of this class is thread-safe.
         * */
        class ExecutionQueue: public Executable
        {
            private:
                /**
                 * \brief The priority queue where executables are stored.
                 * */
                void* queue;

                /**
                 * \brief Mutex used to synchronize access to the queue.
                 * */
                std::mutex mutex;

            public:
                /**
                 * \brief Create an empty execution queue.
                 * */
                ExecutionQueue();

                virtual ~ExecutionQueue();

                /**
                 * \brief Push an Executable object to the queue.
                 * \param executable The executable object to push.
                 * \param priority The priority of object execution. Default is ExecutionPriority::DEFAULT.
                 * */
                void push(std::shared_ptr<Executable> executable, ExecutionPriority priority = ExecutionPriority::DEFAULT);

                /**
                 * \brief Pop the Executable object at the top of the queue.
                 * \return The popped Executable.
                 * */
                std::shared_ptr<Executable> pop();

                /**
                 * \brief Pop and execute the Executable at the top of the queue.
                 * */
                virtual void execute();

                /**
                 * \brief Tells if queue is empty.
                 * \return \c True if queue is empty, false otherwise.
                 * */
                bool isEmpty();
        };
    }
}

#endif
