#include <ege/flow/scene.hxx>
#include <ege/engine.hxx>

namespace ege
{
    namespace flow
    {
        Scene::Scene()
        {
            nextScene = nullptr;
            stopRequired = false;
            restartRequired = false;
        }

        Scene::~Scene()
        {

        }

        void Scene::setNextScene(std::shared_ptr<Scene> scene)
        {
            nextScene = scene;
        }

        void Scene::requireEngineStop()
        {
            stopRequired = true;
            engine::logger->log(log::Level::INFO, "engine stop required");
        }

        void Scene::requireEngineRestart()
        {
            restartRequired = true;
            stopRequired = true;
            engine::logger->log(log::Level::INFO, "engine restart required");
        }

        std::shared_ptr<Scene> Scene::getNextScene() const
        {
            return nextScene;
        }

        bool Scene::isStopRequired() const
        {
            return stopRequired;
        }

        bool Scene::isRestartRequired() const
        {
            return restartRequired;
        }

        void Scene::shouldClose()
        {
            requireEngineStop();
        }
    }
}
