#include <private/ege/flow/ege-start-scene.hxx>
#include <ege/opengl/framebuffer.hxx>

namespace ege
{
    namespace flow
    {
        EGEStartScene::EGEStartScene(std::shared_ptr<Scene> initialScene):
            Scene("ege.StartScene"),
            initialScene(initialScene),
            elapsedTime(0)
        {

        }

        EGEStartScene::~EGEStartScene()
        {

        }

        void EGEStartScene::performUpdate(const Frame& frame)
        {
            elapsedTime += frame.delta;

            if (elapsedTime > 0.0f)
                setNextScene(initialScene);

            opengl::setClearColor(0.0f, 0.0f, 0.0f);
            opengl::clear(opengl::FBOBuffer::COLOR);
        }
    }
}
