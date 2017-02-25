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

        void ControlThread::execute()
        {
            while (true)
            {
                const float delta = 1.0f / 60.0f;
                time::TimeStamp<float> stamp;

                if (engine::isStopRequired())
                    break;

                engine::getGraphicExecutor().execute([&]()
                    {
                        glfwPollEvents();
                        glfwPollEvents(); // solve bug: glfw perform a key repressed after key repeating

                        if (engine::getGLFWWindow().shouldClose())
                            currentScene->shouldClose();

                        if (engine::isStopRequired())
                            return;

                        currentScene->update(delta);

                        if (engine::isStopRequired())
                            return;

                        std::shared_ptr<flow::Scene> nextScene = currentScene->getNextScene();

                        if (nextScene.get() != nullptr)
                        {
                            engine::getLogger().log(log::Level::INFO, "scene change required (%s -> %s)",
                                currentScene->getIdentification().c_str(),
                                nextScene->getIdentification().c_str());

                            currentScene = nextScene;

                            engine::getLogger().log(log::Level::INFO, "new current scene: %s ",
                                currentScene->getIdentification().c_str());
                        }
                        else
                        {
                            currentScene->render();
                            engine::getGLFWWindow().swapBuffers();
                        }
                    });

                stamp.waitUntil(delta);
            }
        }
    }
}
