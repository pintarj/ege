#include <ege/flow/scene.hxx>
#include <ege/engine.hxx>

namespace ege
{
    namespace flow
    {
        Scene::Scene(const std::string identification):
            identification(identification)
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
            engine::logger->log(log::Level::INFO, "engine stop required (by scene %s)", identification.c_str());
        }

        void Scene::requireEngineRestart()
        {
            restartRequired = true;
            stopRequired = true;
            engine::logger->log(log::Level::INFO, "engine restart required (by scene %s)", identification.c_str());
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

        const std::string& Scene::getIdentification() const
        {
            return identification;
        }
    }
}
