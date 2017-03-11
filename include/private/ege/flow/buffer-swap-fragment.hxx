
#ifndef EGE_FLOW_BUFFERSWAPFRAGMENT_HXX
#define EGE_FLOW_BUFFERSWAPFRAGMENT_HXX

#include <ege/flow/fragment.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Swaps the OpenGL's context default framebuffer.
         * */
        class BufferSwapFragment: public Fragment
        {
            protected:
                /**
                 * \brief Swap window's buffers.
                 * \param frame The frame that is updating.
                 * */
                virtual void performUpdate(const Frame& frame);

            public:
                /**
                 * \brief Create a buffer swap fragment.
                 * */
                BufferSwapFragment();

                virtual ~BufferSwapFragment() {}
        };
    }
}

#endif
