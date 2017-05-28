#include <ege/flow/fps-analyzer.hxx>
#include <ege/engine/resources.hxx>

#define N_OF_SAMPLES (32)

namespace ege
{
    namespace flow
    {
        FPSAnalyzer::FPSAnalyzer(std::chrono::microseconds expectedFPS):
            index(0),
            samples(new std::chrono::microseconds[N_OF_SAMPLES]),
            sum(N_OF_SAMPLES * expectedFPS),
            FPS(((float) (N_OF_SAMPLES * 1000000)) / (float) sum.count())
        {
            for (unsigned i = 0; i < N_OF_SAMPLES; ++i)
                samples[i] = std::chrono::microseconds(expectedFPS);
        }

        FPSAnalyzer::~FPSAnalyzer()
        {
            delete[] samples;
        }

        void FPSAnalyzer::frameUpdated(const Frame& frame)
        {
            index = (index + 1) % N_OF_SAMPLES;
            auto lastSample = samples[index];
            auto duration = frame.timePoint - frame.prevTimePoint;
            auto newSample = std::chrono::duration_cast<std::chrono::microseconds>(duration);
            sum += newSample;
            sum -= lastSample;
            samples[index] = newSample;
            FPS = ((float) (N_OF_SAMPLES * 1000000)) / (float) sum.count();
        }

        float FPSAnalyzer::getFPS() const noexcept
        {
            return FPS;
        }
    }
}
