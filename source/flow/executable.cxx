#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        Executable::Executable(ExecutableCPUUsage CPUUsage):
            CPUUsage(CPUUsage)
        {

        }

        ExecutableCPUUsage Executable::getCPUUsage() const
        {
            return CPUUsage;
        }

        FunctionWrapperExecutable::FunctionWrapperExecutable(const std::function<void()>& function,
                ExecutableCPUUsage CPUUsage):
            Executable(CPUUsage),
            function(function)
        {

        }

        void FunctionWrapperExecutable::execute()
        {
            function();
        }
    }
}
