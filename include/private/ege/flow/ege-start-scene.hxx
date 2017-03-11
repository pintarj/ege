
#ifndef EGE_FLOW_EGESTARTSCENE_HXX
#define EGE_FLOW_EGESTARTSCENE_HXX

#include <memory>
#include <ege/flow/scene.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief The EGE start scene.
         *
         * The engine start scene can be skipped at start if ege::engine::Configuration::skipStartScene()
         * returns \c true.
         * */
        class EGEStartScene: public Scene
        {
            private:
                /**
                 * \brief Stores the initial scene defined by engine configuration.
                 * */
                std::shared_ptr<Scene> initialScene;

                /**
                 * \brief Stores the elapsed time since the scene was
                 * */
                float elapsedTime;

            protected:
                /**
                 * \brief Update the scene.
                 * \param frame The updating frame.
                 * */
                void performUpdate(const Frame& frame) override;

            public:
                /**
                 * \brief Create the EGE start scene.
                 * \param initialScene The initial scene defined by engine configuration.
                 * */
                EGEStartScene(std::shared_ptr<Scene> initialScene);

                virtual ~EGEStartScene();
        };
    }
}

#endif
