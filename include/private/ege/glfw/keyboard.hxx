
#ifndef EGE_GLFW_KEYBOARD_HXX
#define EGE_GLFW_KEYBOARD_HXX

namespace ege
{
    namespace glfw
    {
        class Keyboard;
    }
}

#include <set>
#include <ege/keyboard/keyboard.hxx>
#include <private/ege/glfw/window.hxx>

namespace ege
{
    namespace glfw
    {
        /**
         * \brief An implementation of hardware::Keyboard using GLFW.
         * */
        class Keyboard: public keyboard::Keyboard
        {
            private:
                /**
                 * \brief The window that owns \c this keyboard.
                 * */
                const Window& window;

                /**
                 * \brief The listeners that are listening on \c this keyboard.
                 * */
                std::set<keyboard::Listener*> listeners;

            public:
                /**
                 * \brief Create a keyboard that is associated with a Window.
                 * \param window The associated Window.
                 * */
                Keyboard(const Window& window);

                virtual ~Keyboard();

                /**
                 * \brief Tells if a keyboard's key is pressed.
                 * \param key The key to check.
                 * \return \c True if key is pressed.
                 * */
                virtual bool isPressed(keyboard::Key key) const override;

                /**
                 * \brief Add an keyboard::Listener to \c this keyboard.
                 * \param listener The listener to add.
                 * */
                virtual void addListener(keyboard::Listener* listener) override;

                /**
                 * \brief Remove a keyboard::Listener from \c this keyboard.
                 * \param listener The listener to remove.
                 * */
                virtual void removeListener(keyboard::Listener* listener) override;
        };
    }
}

#endif
