
#ifndef EGE_GAME_SCENE_HXX
#define EGE_GAME_SCENE_HXX

namespace ege
{
    namespace game
    {
        class Scene;
    }
}

#include <memory>
#include <ege/engine.hxx>
#include <ege/game/updateable.hxx>

namespace ege
{
    namespace game
    {
        class Scene: public Updateable
        {
                friend Engine;

            private:
                std::shared_ptr<Scene> nextScene;
                bool stopRequired;
                bool restartRequired;

            protected:
                engine::Resources* const engineResources;

                Scene();
                void setNextScene(std::shared_ptr<Scene> scene);
                void requireEngineStop();
                void requireEngineRestart();
                virtual void render() = 0;
                virtual void shouldClose();

            public:
                virtual ~Scene();
                bool isStopRequired() const;
                bool isRestartRequired() const;
        };
    }
}

#endif
