#include <private/ege/game/ege-start-scene.hxx>
#include <ege/opengl/framebuffer.hxx>

namespace ege
{
    namespace game
    {
        EGEStartScene::EGEStartScene(std::shared_ptr<Scene> initialScene):
            initialScene(initialScene),
            elapsedTime(0)
        {

        }

        EGEStartScene::~EGEStartScene()
        {

        }

        void EGEStartScene::performUpdate(float delta)
        {
            elapsedTime += delta;

            if (elapsedTime > 0.0f)
                setNextScene(initialScene);

        }

        void EGEStartScene::render()
        {
            opengl::setClearColor(0.0f, 0.0f, 0.0f);
            opengl::clear(opengl::FBOBuffer::COLOR);
        }
    }
}
