#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        FunctionExecutable::FunctionExecutable(const std::function<void()>& function):
            function(function)
        {

        }

        void FunctionExecutable::execute()
        {
            function();
        }
    }
}
