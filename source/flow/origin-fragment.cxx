#include <private/ege/flow/origin-fragment.hxx>
#include <ege/engine/resources.hxx>
#include <private/ege/flow/buffer-swap-fragment.hxx>

namespace ege
{
    namespace flow
    {
        OriginFragment::OriginFragment(std::shared_ptr<Fragment> initialSceneFragment):
            bufferSwap(new BufferSwapFragment()),
            currentSceneFragment(initialSceneFragment)
        {
            auto eventUpdate = engine::getEventUpdateFragment();
            addDependency(bufferSwap);
            addDependency(eventUpdate);
            bufferSwap->addDependency(eventUpdate);
            bufferSwap->addDependency(initialSceneFragment);
            this->currentSceneFragment = initialSceneFragment;
        }

        void OriginFragment::setCurrentSceneFragment(std::shared_ptr<Fragment> currentSceneFragment)
        {
            bufferSwap->removeDependency(this->currentSceneFragment);
            this->currentSceneFragment = currentSceneFragment;
            bufferSwap->addDependency(currentSceneFragment);
        }
    }
}
