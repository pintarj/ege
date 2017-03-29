
#ifndef EGE_MOUSE_MOUSE_HXX
#define EGE_MOUSE_MOUSE_HXX

#include <ege/mouse/cursor-mode.hxx>
#include <ege/mouse/position-listener.hxx>

namespace ege
{
    namespace mouse
    {
        /**
         * \brief An abstraction of the mouse.
         * */
        class Mouse
        {
            public:
                virtual ~Mouse() {}

                /**
                 * \brief Get the position of the mouse's cursor.
                 * \param x, y [out] The pointers where the values of position will be stored.
                 * */
                virtual void getPosition(double* x, double* y) const = 0;

                /**
                 * \brief Add a PositionListener to \c this mouse.
                 * \param listener The listener to add.
                 * */
                virtual void addPositionListener(PositionListener* listener) = 0;

                /**
                 * \brief Remove a PositionListener to \c this mouse.
                 * \param listener The listener to remove.
                 * */
                virtual void removePositionListener(PositionListener* listener) = 0;

                /**
                 * \brief Set the mode of the cursor.
                 * \param mode The specified cursor mode.
                 * */
                virtual void setCursorMode(CursorMode mode) = 0;
        };
    }
}

#endif
