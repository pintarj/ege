
#ifndef EGE_OPENGL_CONTEXT_HXX
#define EGE_OPENGL_CONTEXT_HXX

#include <ege/opengl/framebuffer.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Represent an OpenGL context wrapper.
         *
         * Context object are non movable or copyable.
         * */
        class Context
        {
            public:
                virtual ~Context() {}

                /**
                 * \brief Returns the default framebuffer of \c this context.
                 * \return The default framebuffer wrapper object.
                 * */
                virtual DefaultFramebuffer& getDefaultFramebuffer() = 0;
        };
    }
}

#endif
