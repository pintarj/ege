
#ifndef EGE_FLOW_ORIGINFRAGMENT_HXX
#define EGE_FLOW_ORIGINFRAGMENT_HXX

#include <ege/flow/fragment.hxx>

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
                 * \brief Stores the buffer swap Fragment.
                 * */
                std::shared_ptr<Fragment> bufferSwap;

                /**
                 * \brief Stores current scene fragment.
                 * */
                std::shared_ptr<Fragment> currentSceneFragment;

            public:
                /**
                 * \brief Create an origin fragment.
                 * \param initialSceneFragment The initial scene fragment.
                 * */
                OriginFragment(std::shared_ptr<Fragment> initialSceneFragment);

                virtual ~OriginFragment() {};

                /**
                 * \brief Set the fragment of current scene (removing previous).
                 * \param currentSceneFragment The current scene fragment.
                 *
                 * Called on scene change.
                 * */
                void setCurrentSceneFragment(std::shared_ptr<Fragment> currentSceneFragment);
        };
    }
}

#endif
