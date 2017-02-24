
#ifndef EGE_FLOW_EXECUTABLE_HXX
#define EGE_FLOW_EXECUTABLE_HXX

#include <functional>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Represent an executable object.
         * */
        class Executable
        {
            public:
                virtual ~Executable() {}

                /**
                 * \brief Implementation should execute something.
                 * */
                virtual void execute() = 0;
        };

        /**
         * \brief Represent a std::function<void()> as an Executable.
         * */
        class FunctionExecutable: public Executable
        {
            private:
                /**
                 * \brief The wrapped function.
                 * */
                std::function<void()> function;

            public:
                /**
                 * \brief Create an Executable object that execute a specified function.
                 * \param function The specified function.
                 * */
                FunctionExecutable(const std::function<void()>& function);

                virtual ~FunctionExecutable() {}

                /**
                 * \brief Execute the specified function.
                 * */
                virtual void execute();
        };
    }
}

#endif
