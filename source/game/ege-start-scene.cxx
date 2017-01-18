#include <private/ege/game/ege-start-scene.hxx>
#include <ege/graphic/gpu/frame-buffer.hxx>

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
            graphic::gpu::frameBuffer::clearColorBuffer(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
}
