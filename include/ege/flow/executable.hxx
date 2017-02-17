
#ifndef EGE_FLOW_EXECUTABLE_HXX
#define EGE_FLOW_EXECUTABLE_HXX

#include <functional>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Enumerate CPU usages of an Executable.
         * \sa Executable
         *
         * That parameter can have a big impact on engine performance, so it's important to set it properly:
         *     - \c EXTREME: No I/O operations required at all.
         *     - \c HIGH: I/O operation are used in very few moments. For example: to load parameters and store results
         *     - \c MEDIUM: I/O operations and CPU are used at the same level. Use this if not sure.
         *         This is the default.
         *     - \c LOW: CPU is used only for manipulation of data in I/O operation. For example: SSL communications,
         *         compressed image loading, ...
         *     - \c ZERO: CPU is (practically) not used. Only I/O operations. For example: uploading/downloading
         *         something, reading from/writing to a file, ...
         * */
        enum class ExecutableCPUUsage: unsigned int
        {
            EXTREME,
            HIGH,
            MEDIUM,
            LOW,
            ZERO,
            DEFAULT = MEDIUM
        };

        /**
         * \brief Represent an executable object.
         * */
        class Executable
        {
            private:
                /**
                 * \brief Stores the CPU usage of \c this Executable.
                 * */
                ExecutableCPUUsage CPUUsage;

            protected:
                /**
                 * \brief Create an executable.
                 * \param CPUUsage The CPU usage of the executable. Default is ExecutableCPUUsage::DEFAULT.
                 * */
                Executable(ExecutableCPUUsage CPUUsage = ExecutableCPUUsage::DEFAULT);

            public:
                virtual ~Executable() {}

                /**
                 * \brief Implementation should execute something.
                 * */
                virtual void execute() = 0;

                /**
                 * \brief Tells which is the CPU usage of \c this Executable.
                 * \return The CPU usage.
                 * */
                ExecutableCPUUsage getCPUUsage() const;
        };

        /**
         * \brief Represent a std::function<void()> wrapped in an Executable.
         * */
        class FunctionWrapperExecutable: public Executable
        {
            private:
                /**
                 * \brief The wrapped function.
                 * */
                std::function<void()> function;

            public:
                /**
                 * \brief Create a function wrapper Executable object.
                 * \param function The function to wrap.
                 * \param CPUUsage The CPU usage of the executable. Default is ExecutableCPUUsage::DEFAULT.
                 * */
                FunctionWrapperExecutable(const std::function<void()>& function,
                    ExecutableCPUUsage CPUUsage = ExecutableCPUUsage::DEFAULT);

                virtual ~FunctionWrapperExecutable() {}

                /**
                 * \brief Execute the wrapped function.
                 * */
                virtual void execute();
        };
    }
}

#endif
