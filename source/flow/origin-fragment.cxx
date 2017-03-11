#include <private/ege/flow/origin-fragment.hxx>
#include <ege/engine/resources.hxx>
#include <private/ege/engine/flow.hxx>
#include <private/ege/flow/buffer-swap-fragment.hxx>

namespace ege
{
    namespace flow
    {
        void OriginFragment::performUpdate(const Frame& frame)
        {
            {
                std::lock_guard<std::mutex>lock (mutex);
                lastUpdated = updating;
            }

            updatedSignal.getNotifier().notifyAll();
        }

        OriginFragment::OriginFragment(std::shared_ptr<Fragment> initialSceneFragment):
            bufferSwap(new BufferSwapFragment()),
            currentSceneFragment(initialSceneFragment),
            lastUpdated(0),
            updating(0),
            updatedSignal(mutex, [this]() -> bool
                {
                    return this->lastUpdated == this->updating;
                })
        {
            auto eventUpdate = engine::getEventUpdateFragment();
            addDependency(bufferSwap);
            addDependency(eventUpdate);
            bufferSwap->addDependency(eventUpdate);
            bufferSwap->addDependency(initialSceneFragment);
            this->currentSceneFragment = initialSceneFragment;
        }

        void OriginFragment::update(const Frame& frame)
        {
            updating = frame.id;
            Fragment::update(frame);
        }

        void OriginFragment::setCurrentSceneFragment(std::shared_ptr<Fragment> currentSceneFragment)
        {
            bufferSwap->removeDependency(this->currentSceneFragment);
            this->currentSceneFragment = currentSceneFragment;
            bufferSwap->addDependency(currentSceneFragment);
        }

        SignalWaiter& OriginFragment::getUpdatedWaiter() const noexcept
        {
            return updatedSignal.getWaiter();
        }
    }
}
