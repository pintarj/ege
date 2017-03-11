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
            currentScene(initialScene)
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
            currentFrame = std::unique_ptr<flow::Frame>(new flow::Frame(updateTime, lastFrameUpdate));
            lastFrameUpdate = updateTime;
            getOriginFragment().update(*currentFrame);
        }

        void ControlThread::execute()
        {
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
