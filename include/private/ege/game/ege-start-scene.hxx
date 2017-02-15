
#ifndef EGE_GAME_EGESTARTSCENE_HXX
#define EGE_GAME_EGESTARTSCENE_HXX

#include <memory>
#include <ege/game/scene.hxx>

namespace ege
{
    namespace game
    {
        class EGEStartScene: public Scene
        {
            private:
                std::shared_ptr<Scene> initialScene;
                float elapsedTime;

            public:
                EGEStartScene(std::shared_ptr<Scene> initialScene);
                virtual ~EGEStartScene();
                void performUpdate(float delta);
                void render();
        };
    }
}

#endif
