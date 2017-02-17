
#ifndef EGE_FLOW_THREAD_HXX
#define EGE_FLOW_THREAD_HXX

#include <atomic>
#include <thread>
#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief A thread implementation.
         * \sa start()
         * \sa join()
         * */
        class Thread
        {
            private:
                /**
                 * \brief The C++ thread used as back.
                 * */
                std::unique_ptr<std::thread> thread;

                /**
                 * \brief The executable to execute on the thread.
                 * */
                std::shared_ptr<Executable> executable;

                /**
                 * \brief Tells if the thread has been started.
                 * */
                std::atomic_bool started;

                /**
                 * \brief Tells if the thread has been joined.
                 * */
                std::atomic_bool joined;

            public:
                /**
                 * \brief Create a thread with the specified Executable to execute.
                 *
                 * Creating the Thread wouldn't start executing the Executable object.
                 * Method Thread::start() has to be invoked.
                 * */
                Thread(std::shared_ptr<Executable> executable);

                /**
                 * \brief Destroys the thread.
                 *
                 * If the thread was not joined manually, then will be joined by destructor and
                 * a warning will be logged.
                 * */
                virtual ~Thread();

                /**
                 * \brief Starts the execution of the executable on the thread.
                 * */
                void start();

                /**
                 * \brief Join the thread.
                 *
                 * Each thread has to be manually joined before destruction, otherwise the destructor will
                 * automatically join the thread, but a warning will be logged.
                 * */
                void join();

                /**
                 * \brief Tells if the thread has been started.
                 * \return \c True if has been started.
                 * */
                bool isStarted() const noexcept;

                /**
                 * \brief Tells if the thread has been joined.
                 * \return \c True if has been joined.
                 * */
                bool isJoined() const noexcept;
        };

        /**
         * \brief Return the number of running native threads created by class ege::flow::Thread objects.
         * \return The number of running native threads.
         * */
        unsigned getRunningThreadCount() noexcept;
    }
}

#endif
