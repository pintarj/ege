
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
        class Thread: protected Executable
        {
            private:
                /**
                 * \brief The C++ thread used as back.
                 * */
                std::unique_ptr<std::thread> thread;

                /**
                 * \brief Stores the executable specified in constructor.
                 * */
                std::shared_ptr<Executable> executable;

                /**
                 * \brief The executable to execute on the thread.
                 */
                Executable& toExecute;

                /**
                 * \brief Tells if the thread has been started.
                 * */
                std::atomic_bool started;

                /**
                 * \brief Tells if the thread has been joined.
                 * */
                std::atomic_bool joined;

                /**
                 * \brief Tells if the thread is running.
                 * */
                std::atomic_bool running;

            protected:
                /**
                 * \brief If no executable is specified in constructor, this method will be executed on thread.
                 *
                 * Default implementation is an empty function.
                 * */
                virtual void execute();

            public:
                /**
                 * \brief The name of the thread.
                 * */
                const std::string name;

                /**
                 * \brief Create a thread.
                 *
                 * The name of the thread will be automatically assigned. \n
                 * The thread will execute the protected method Thread::execute(). \n
                 * Creating the Thread wouldn't start executing the Executable object.
                 * Method Thread::start() has to be invoked.
                 * */
                Thread();

                /**
                 * \brief Create a thread with the specified Executable to execute.
                 * \param executable The executable.
                 *
                 * The name of the thread will be automatically assigned. \n
                 * Creating the Thread wouldn't start executing the Executable object.
                 * Method Thread::start() has to be invoked.
                 * */
                Thread(std::shared_ptr<Executable> executable);

                /**
                 * \brief Create a thread with the specified name.
                 * \param name The name of the thread.
                 *
                 * The thread will execute the protected method Thread::execute(). \n
                 * Creating the Thread wouldn't start executing the Executable object.
                 * Method Thread::start() has to be invoked.
                 * */
                Thread(const std::string& name);

                /**
                 * \brief Create a thread with the specified name.
                 * \param executable The executable.
                 * \param name The name of the thread.
                 *
                 * Creating the Thread wouldn't start executing the Executable object.
                 * Method Thread::start() has to be invoked.
                 * */
                Thread(std::shared_ptr<Executable> executable, const std::string& name);

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

                /**
                 * \brief Tells if the thread is running.
                 * \return \c True if is running, false otherwise.
                 * */
                bool isRunning() const noexcept;
        };

        /**
         * \brief Return the number of running native threads created by class ege::flow::Thread objects.
         * \return The number of executing native threads.
         * */
        unsigned getExecutingThreadCount() noexcept;
    }
}

#endif
