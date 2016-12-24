

#ifndef EGE_GAME_SCENE_HXX
#define EGE_GAME_SCENE_HXX


#include <ege/engine.hxx>
#include <ege/game/updateable.hxx>


namespace ege
{
        class Engine;

        namespace engine
        {
                class Resources;
        }

        namespace game
        {
                class Scene: public Updateable
                {
                        friend Engine;

                        private:
                                Scene* nextScene;
                                bool stopEngine;
                                bool restartEngine;
                                bool deleteOnExchange;

                        protected:
                                engine::Resources* const engineResources;

                                Scene();
                                void setNextScene( Scene& scene );
                                void requireEngineStop();
                                void requireEngineRestart();
                                void doNotDeleteOnExchange();
                                virtual void render() = 0;
                                virtual void shouldClose();

                        public:
                                virtual ~Scene();
                };
        }
}


#endif
