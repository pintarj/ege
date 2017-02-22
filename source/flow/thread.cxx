#include <ege/flow/thread.hxx>
#include <mutex>
#include <unordered_map>
#include <ege/engine.hxx>
#include <ege/exception.hxx>

namespace ege
{
    namespace flow
    {
        static std::unordered_map<std::thread::id, Thread*> threads;
        static std::mutex mutex;

        void Thread::execute()
        {

        }

        Thread::Thread(std::shared_ptr<Executable> executable):
            executable(executable),
            toExecute(*executable),
            started(false),
            joined(false)
        {

        }

        Thread::Thread():
            executable(nullptr),
            toExecute(*this),
            started(false),
            joined(false)
        {

        }

        Thread::~Thread()
        {
            if (started && !isJoined())
            {
                engine::logger->log(log::Level::WARNING, "thread was started but not manually joined\n"
                    "(joining now at thread destruction)");

                join();
            }
        }

        void Thread::start()
        {
            if (this->started.exchange(true))
                exception::throwNew("starting an already started thread");

            thread = std::unique_ptr<std::thread>(new std::thread([this]()
                {
                    std::thread::id id = std::this_thread::get_id();

                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        threads[id] = this;
                    }

                    this->toExecute.execute();

                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        threads.erase(id);
                    }
                }));
        }

        void Thread::join()
        {
            if (!started)
            {
                engine::logger->log(log::Level::WARNING, "joining thread that was never started");
                return;
            }

            if (joined.exchange(true))
            {
                engine::logger->log(log::Level::WARNING, "joining thread that was already joined");
                return;
            }

            thread->join();
        }

        bool Thread::isStarted() const noexcept
        {
            return started;
        }

        bool Thread::isJoined() const noexcept
        {
            return joined;
        }

        unsigned getExecutingThreadCount() noexcept
        {
            std::unique_lock<std::mutex> lock(mutex);
            return (unsigned) threads.size();
        }
    }
}
