#include <ege/flow/executor.hxx>

namespace ege
{
    namespace flow
    {
        void Executor::execute(std::shared_ptr<Executable> executable)
        {
            executable->execute();
        }
    }
}
