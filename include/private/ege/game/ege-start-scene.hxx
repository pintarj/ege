

#ifndef EGE_GAME_EGESTARTSCENE_HXX
#define EGE_GAME_EGESTARTSCENE_HXX


#include <ege/game/scene.hxx>
#include <ege/graphic/gpu/buffer.hxx>


namespace ege
{
        namespace game
        {
                class EGEStartScene: public Scene
                {
                        private:
                                Scene& initialScene;
                                float elapsedTime;

                        public:
                                EGEStartScene( Scene& initialScene );
                                virtual ~EGEStartScene();
                                void performUpdate( float delta );
                                void render();
                };
        }
}


#endif
