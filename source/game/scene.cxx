#include <ege/game/scene.hxx>

namespace ege
{
    namespace game
    {
        Scene::Scene():
            engineResources(ege::engine::resources)
        {
            nextScene = nullptr;
            stopRequired = false;
            restartRequired = false;
        }

        void Scene::setNextScene(std::shared_ptr<Scene> scene)
        {
            nextScene = scene;
        }

        void Scene::requireEngineStop()
        {
            stopRequired = true;
            engineResources->logger->log(util::log::Level::INFO, "engine stop required");
        }

        void Scene::requireEngineRestart()
        {
            restartRequired = true;
            stopRequired = true;
            engineResources->logger->log(util::log::Level::INFO, "engine restart required");
        }

        void Scene::shouldClose()
        {
            requireEngineStop();
        }

        Scene::~Scene()
        {

        }

        bool Scene::isStopRequired() const
        {
            return stopRequired;
        }

        bool Scene::isRestartRequired() const
        {
            return restartRequired;
        }
    }
}
