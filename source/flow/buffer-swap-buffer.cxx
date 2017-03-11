#include <private/ege/flow/buffer-swap-fragment.hxx>
#include <private/ege/engine/resources.hxx>

namespace ege
{
    namespace flow
    {
        BufferSwapFragment::BufferSwapFragment()
        {

        }

        void BufferSwapFragment::performUpdate(const Frame& frame)
        {
            engine::getGLFWWindow().swapBuffers();
        }
    }
}
