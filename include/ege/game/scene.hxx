
#ifndef EGE_GAME_SCENE_HXX
#define EGE_GAME_SCENE_HXX

#include <memory>
#include <ege/game/updateable.hxx>

namespace ege
{
    namespace game
    {
        /**
         * \brief A class that describes a game scenario.
         * */
        class Scene: public Updateable
        {
            private:
                /**
                 * \brief Contains the next Scene.
                 * */
                std::shared_ptr<Scene> nextScene;

                /**
                 * \brief Tells if an engine stop it was required.
                 * */
                bool stopRequired;

                /**
                 * \brief Tells if an engine restart it was required.
                 * */
                bool restartRequired;

            public:
                /**
                 * \brief Create a Scene.
                 * */
                Scene();

                virtual ~Scene();

                /**
                 * \brief Set the next Scene to
                 * \param scene The next Scene.
                 * */
                void setNextScene(std::shared_ptr<Scene> scene);

                /**
                 * \brief Requires the stop of the engine.
                 *
                 * This method should be called while engine is updating the Scene (Scene::performUpdate()).
                 * After the call of that method the engine will check if an engine stop was required and
                 * will eventually stop.
                 * */
                void requireEngineStop();

                /**
                 * \brief Requires the restart of the engine.
                 *
                 * This method should be called while engine is updating the Scene (Scene::performUpdate()).
                 * After the call of that method the engine will check if an engine restart was required and
                 * will eventually restart.
                 * */
                void requireEngineRestart();

                /**
                 * \brief Returns the next Scene.
                 * \sa setNextScene()
                 * */
                std::shared_ptr<Scene> getNextScene() const;

                /**
                 * \brief Tells if engine stop is required.
                 * \return \c True is engine stop is required.
                 * */
                bool isStopRequired() const;

                /**
                 * \brief Tells if engine restart is required.
                 * \return \c True is engine restart is required.
                 * */
                bool isRestartRequired() const;

                /**
                 * \brief Called by engine when it should be closed.
                 *
                 * An example when engine will call this method is the press of \c alt+F4.
                 * The default implementation requires an engine stop with Scene::requireEngineStop().
                 * */
                virtual void shouldClose();

                /**
                 * \brief Called by engine when a frame have to be rendered.
                 * */
                virtual void render() = 0;
        };
    }
}

#endif
