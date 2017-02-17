
#ifndef EGE_FLOW_EXECUTOR_HXX
#define EGE_FLOW_EXECUTOR_HXX

#include <memory>
#include <ege/flow/executable.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Executor executes Executable objects (Executable::execute()) following some criteria.
         * */
        class Executor
        {
            public:
                virtual ~Executor() {}

                /**
                 * \brief Implementation should (in some way) invoke Executable::execute() method of the
                 *     specified Executable object.
                 * \param executable The specified Executable to execute.
                 *
                 * Default implementation simply invoke Executable::execute() method of the
                 *     specified Executable object.
                 * */
                virtual void execute(std::shared_ptr<Executable> executable);
        };
    }
}

#endif
