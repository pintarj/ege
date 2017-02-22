#include <ege/flow/executor.hxx>

namespace ege
{
    namespace flow
    {
        void Executor::execute(std::shared_ptr<Executable> executable)
        {
            executable->execute();
        }

        void PriorityExecutor::execute(std::shared_ptr<Executable> executable, Priority priority)
        {
            executable->execute();
        }

        void PriorityExecutor::execute(std::shared_ptr<Executable> executable)
        {
            execute(executable, Priority::DEFAULT);
        }
    }
}
