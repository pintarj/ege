
#ifndef EGE_FLOW_FPSANALYZER_HXX
#define EGE_FLOW_FPSANALYZER_HXX

#include <chrono>
#include <ege/flow/frame.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Analyzes and estimate FPS value.
         * */
        class FPSAnalyzer
        {
            private:
                /**
                 * \brief Here are stored last N collected samples.
                 * */
                std::chrono::microseconds* samples;

                /**
                 * \brief The index of the last collected sample.
                 * */
                unsigned index;

                /**
                 * \brief The sum of all N last samples.
                 * */
                std::chrono::microseconds sum;

                /**
                 * \brief The approximation of FPS value.
                 * */
                float FPS;

            public:
                /**
                 * \brief Creates an FPS analyzer.
                 * \param expectedFPS The initial value of N collected samples.
                 * */
                FPSAnalyzer(std::chrono::microseconds expectedFPS = std::chrono::microseconds(16667));

                virtual ~FPSAnalyzer();

                /**
                 * \brief Update the sample collection adding a new frame duration (the last will be removed).
                 * \param frame The frame which duration is added to sample collection.
                 * */
                void frameUpdated(const Frame& frame);

                /**
                 * \brief Returns the approximation of the FPS value.
                 * \return The approximation of the FPS value.
                 * */
                float getFPS() const noexcept;
        };
    }
}

#endif
