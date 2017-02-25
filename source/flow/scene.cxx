#include <ege/flow/scene.hxx>
#include <ege/engine/flow.hxx>
#include <ege/engine/resources.hxx>

namespace ege
{
    namespace flow
    {
        Scene::Scene(const std::string identification):
            identification(identification)
        {
            nextScene = nullptr;
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
            engine::requireStop();
        }

        void Scene::requireEngineRestart()
        {
            engine::requireRestart();
        }

        std::shared_ptr<Scene> Scene::getNextScene() const
        {
            return nextScene;
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
