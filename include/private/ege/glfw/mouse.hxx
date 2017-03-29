
#ifndef PRIVATE_EGE_GLFW_MOUSE_HXX
#define PRIVATE_EGE_GLFW_MOUSE_HXX

namespace ege
{
    namespace glfw
    {
        class Mouse;
    }
}

#include <set>
#include <ege/mouse/mouse.hxx>
#include <private/ege/glfw/window.hxx>

namespace ege
{
    namespace glfw
    {
        /**
         * \brief An implementation of mouse::Mouse using GLFW.
         * */
        class Mouse: public mouse::Mouse
        {
            private:
                /**
                 * \brief The window that owns \c this mouse.
                 * */
                const Window& window;

                /**
                 * \brief The listeners that are listening cursor position on \c this mouse.
                 * */
                std::set<mouse::PositionListener*> positionListeners;

            public:
                Mouse(const Window& window);

                virtual ~Mouse();

                /**
                 * \brief Get the position of the mouse's cursor.
                 * \param x, y [out] The pointers where the values of position will be stored.
                 * */
                virtual void getPosition(double* x, double* y) const override;

                /**
                 * \brief Add a mouse::PositionListener to \c this mouse.
                 * \param listener The listener to add.
                 * */
                virtual void addPositionListener(mouse::PositionListener* listener) override;

                /**
                 * \brief Remove a mouse::PositionListener to \c this mouse.
                 * \param listener The listener to remove.
                 * */
                virtual void removePositionListener(mouse::PositionListener* listener) override;
        };
    }
}

#endif
