
#ifndef EGE_OPENGL_VIEWPORT_HXX
#define EGE_OPENGL_VIEWPORT_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Set the viewport.
         * \param x, y Specify the lower left corner of the viewport rectangle, in pixels. The initial value is (0,0).
         * \param width, height Specify the width and height of the viewport.
         *
         * When a GL context is first attached to a window, width and height are set to the dimensions of that window.
         * */
        void viewport(int x, int y, int width, int height);
    }
}

#endif
