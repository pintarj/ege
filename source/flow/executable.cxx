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
    }
}
