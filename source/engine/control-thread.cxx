#include <private/ege/engine/control-thread.hxx>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ege/engine/resources.hxx>
#include <ege/time/time-stamp.hxx>
#include <private/ege/engine/flow.hxx>
#include <private/ege/engine/resources.hxx>

namespace ege
{
    namespace engine
    {
        ControlThread::ControlThread(std::shared_ptr<flow::Scene> initialScene):
            Thread("ege-control"),
            currentScene(initialScene),
            preparingGraphExecution(false),
            graphPreparedSignal(graphPreparationMutex, [this]() { return !preparingGraphExecution; })
        {

        }

        ControlThread::~ControlThread()
        {

        }

        void ControlThread::checkNextScene()
        {
            std::shared_ptr<flow::Scene> nextScene = currentScene->getNextScene();

            if (nextScene.get() != nullptr)
            {
                engine::getLogger().log(log::Level::INFO, "scene change required (%s -> %s)",
                    currentScene->getIdentification().c_str(),
                    nextScene->getIdentification().c_str());

                currentScene = nextScene;
                getOriginFragment().setCurrentSceneFragment(currentScene);

                engine::getLogger().log(log::Level::INFO, "new current scene: %s ",
                    currentScene->getIdentification().c_str());
            }
        }

        void ControlThread::requireNextFrameRendering(flow::Frame::TimePoint updateTime)
        {
            std::shared_ptr<flow::Executable> waitCode(new flow::FunctionExecutable([this]()
                {
                    graphPreparedSignal.getWaiter().wait();
                }));

            {
                std::lock_guard<std::mutex> lock(graphPreparationMutex);
                preparingGraphExecution = true;

                engine::getGraphicExecutor().execute(waitCode);
                auto& nucleus = engine::getParallelNucleus();
                for (unsigned i = 0, n = nucleus.getNumberOfThreads(); i < n; ++i)
                    nucleus.execute(waitCode);

                currentFrame = std::unique_ptr<flow::Frame>(new flow::Frame(updateTime, lastFrameUpdate));
                lastFrameUpdate = updateTime;
                engine::getNonConstFPSAnalyzer().frameUpdated(*currentFrame);
                getOriginFragment().update(*currentFrame);
                preparingGraphExecution = false;
            }

            graphPreparedSignal.getNotifier().notifyAll();
        }

        void ControlThread::execute()
        {
            lastFrameUpdate = std::chrono::steady_clock::now();

            while (true)
            {
                if (engine::isStopRequired())
                    break;

                checkNextScene();
                requireNextFrameRendering();
                getOriginFragment().getUpdatedWaiter().wait();
            }
        }

        flow::Scene& ControlThread::getCurrentScene() const noexcept
        {
            return *currentScene;
        }
    }
}
