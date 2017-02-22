
#ifndef EGE_FLOW_EXECUTOR_HXX
#define EGE_FLOW_EXECUTOR_HXX

#include <memory>
#include <ege/flow/executable.hxx>
#include <ege/flow/priority.hxx>

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

        /**
         * \brief Executor executes Executable objects (Executable::execute()) following some criteria that
         *     consider an execution priority.
         * */
        class PriorityExecutor: public Executor
        {
            public:
                virtual ~PriorityExecutor() {}

                /**
                 * \brief Implementation should (in some way) invoke Executable::execute() method of the
                 *     specified Executable object, considering the execution priority.
                 * \param executable The specified Executable to execute.
                 * \param priority The priority of execution.
                 *
                 * Default implementation simply invoke Executable::execute() method of the
                 *     specified Executable object.
                 * */
                virtual void execute(std::shared_ptr<Executable> executable, Priority priority);

                /**
                 * \brief Implementation will invoke execute(std::shared_ptr<Executable>, Priority) method
                 *     forwarding executable as first parameter and Priority::DEFAULT as priority.
                 * \param executable The specified Executable to execute.
                 * */
                virtual void execute(std::shared_ptr<Executable> executable) final;
        };
    }
}

#endif
