
#ifndef EGE_FLOW_ORIGINFRAGMENT_HXX
#define EGE_FLOW_ORIGINFRAGMENT_HXX

#include <mutex>
#include <ege/flow/fragment.hxx>
#include <ege/flow/signal.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief The origin Fragment.
         * */
        class OriginFragment: public Fragment
        {
            private:
                /**
                 * \brief Stores current scene fragment.
                 * */
                std::shared_ptr<Fragment> currentSceneFragment;

                /**
                 * \brief Used to synchronize signals.
                 */
                std::mutex mutex;

                /**
                 * \brief Signal used to notify that \c this object has been updated.
                 * */
                Signal updatedSignal;

                /**
                 * \brief Contains the id of the last (totally) updated/rendered frame.
                 * */
                Frame::Id lastUpdated;

                /**
                 * \brief Contains the id of the last updated/rendered frame (can also be updating meantime).
                 * */
                Frame::Id updating;

            protected:
                /**
                 * \brief Notify that the frame has been updated/rendered.
                 * */
                void performUpdate(const Frame& frame) override;

            public:
                /**
                 * \brief Create an origin fragment.
                 * \param initialSceneFragment The initial scene fragment.
                 * */
                OriginFragment(std::shared_ptr<Fragment> initialSceneFragment);

                virtual ~OriginFragment() {};

                /**
                 * \brief Stores the id of the updating frame and calls Fragment::update().
                 * \param frame The updating frame.
                 * */
                virtual void update(const Frame& frame) override;

                /**
                 * \brief Set the fragment of current scene (removing previous).
                 * \param currentSceneFragment The current scene fragment.
                 *
                 * Called on scene change.
                 * */
                void setCurrentSceneFragment(std::shared_ptr<Fragment> currentSceneFragment);

                /**
                 * \brief Returns the SignalWaiter, that is notified when \c this is updated (frame has
                 *     been updated/rendered).
                 * \return The SignalWaiter.
                 * */
                SignalWaiter& getUpdatedWaiter() const noexcept;
        };
    }
}

#endif
