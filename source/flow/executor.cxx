#include <ege/flow/executor.hxx>

namespace ege
{
    namespace flow
    {
        void Executor::execute(std::shared_ptr<Executable> executable)
        {
            executable->execute();
        }

        void Executor::execute(const std::function<void()>& function)
        {
            execute(std::shared_ptr<Executable>(new FunctionExecutable(function)));
        }

        void PriorityExecutor::execute(std::shared_ptr<Executable> executable, Priority priority)
        {
            executable->execute();
        }

        void PriorityExecutor::execute(std::shared_ptr<Executable> executable)
        {
            execute(executable, Priority::DEFAULT);
        }

        void PriorityExecutor::execute(const std::function<void()>& function, Priority priority)
        {
            execute(std::shared_ptr<Executable>(new FunctionExecutable(function)), priority);
        }
    }
}
