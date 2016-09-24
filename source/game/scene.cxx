#include <ege/game/scene.hxx>


using namespace ege;
using namespace ege::game;


Scene::Scene(): engineResources( ege::engine::resources )
{
        nextScene = nullptr;
        stopEngine = false;
        restartEngine = false;
}


void Scene::setNextScene( Scene &scene )
{
        nextScene = &scene;
}


void Scene::requireEngineStop()
{
        stopEngine = true;
        engineResources->logger->log( util::log::Level::INFO, "engine stop required" );
}


void Scene::requireEngineRestart()
{
        restartEngine = true;
        stopEngine = true;
        engineResources->logger->log( util::log::Level::INFO, "engine restart required" );
}


void Scene::shouldClose()
{
        requireEngineStop();
}


Scene::~Scene()
{

}
