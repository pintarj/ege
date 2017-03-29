
#ifndef EGE_MOUSE_POSITION_LISTENER_HXX
#define EGE_MOUSE_POSITION_LISTENER_HXX

namespace ege
{
    namespace mouse
    {
        /**
         * \brief The cursor position change event listener.
         * */
        class PositionListener
        {
            public:
                virtual ~PositionListener() {}

                /**
                 * \brief Called when the position of cursor is changed.
                 * \param x, y The position relative to the left top corner of the window client area.
                 */
                virtual void onPositionChange(double x, double y) {};
        };
    }
}

#endif
