#include <ege/flow/thread.hxx>
#include <private/ege/flow/thread.hxx>
#include <private/ege/flow/thread.hxx>
#include <mutex>
#include <unordered_map>
#include <ege/exception.hxx>
#include <ege/engine/resources.hxx>

#ifdef __unix__
#include <pthread.h>
#endif

namespace ege
{
    namespace flow
    {
        static std::unordered_map<std::thread::id, Thread*> threads;
        static std::mutex mutex;
        static unsigned number = 0;

        static inline std::string generateAThreadName()
        {
            return "ege-thread-" + std::to_string(number++);
        }

        void Thread::execute()
        {

        }

        Thread::Thread(std::shared_ptr<Executable> executable, const std::string& name):
            executable(executable),
            toExecute(*executable),
            started(false),
            joined(false),
            running(false),
            name(name)
        {

        }

        Thread::Thread(std::shared_ptr<Executable> executable):
            Thread(executable, generateAThreadName())
        {

        }

        Thread::Thread(const std::string& name):
            executable(nullptr),
            toExecute(*this),
            started(false),
            joined(false),
            running(false),
            name(name)
        {

        }

        Thread::Thread():
            Thread(generateAThreadName())
        {

        }

        Thread::~Thread()
        {
            if (started && !isJoined())
            {
                engine::getLogger().log(log::Level::WARNING, "thread was started but not manually joined\n"
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

                    flow::changeThisThreadName(this->name);
                    this->running = true;
                    this->toExecute.execute();
                    this->running = false;

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
                engine::getLogger().log(log::Level::WARNING, "joining thread that was never started");
                return;
            }

            if (joined.exchange(true))
            {
                engine::getLogger().log(log::Level::WARNING, "joining thread that was already joined");
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

        bool Thread::isRunning() const noexcept
        {
            return running;
        }

        unsigned getExecutingThreadCount() noexcept
        {
            std::unique_lock<std::mutex> lock(mutex);
            return (unsigned) threads.size();
        }

        bool changeThisThreadName(const std::string& name)
        {
#ifdef __unix__
            pthread_setname_np(pthread_self(), name.c_str());
            return true;
#else
            return false;
#endif
        }
    }
}
