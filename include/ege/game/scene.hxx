

#ifndef EGE_GAME_SCENE_HXX
#define EGE_GAME_SCENE_HXX


#include <ege/engine.hxx>


namespace ege
{
        class Engine;

        namespace engine
        {
                class Resources;
        }

        namespace game
        {
                class Scene
                {
                        friend Engine;

                        private:
                                Scene* nextScene;
                                bool stopEngine;
                                bool restartEngine;

                        protected:
                                engine::Resources* const engineResources;

                                Scene();
                                void setNextScene( Scene& scene );
                                void requireEngineStop();
                                void requireEngineRestart();
                                virtual void update( float delta ) = 0;
                                virtual void render() = 0;
                                virtual void shouldClose();

                        public:
                                virtual ~Scene();
                };
        }
}


#endif
