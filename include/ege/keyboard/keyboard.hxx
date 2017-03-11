
#ifndef EGE_KEYBOARD_KEYBOARD_HXX
#define EGE_KEYBOARD_KEYBOARD_HXX

#include <ege/keyboard/key.hxx>
#include <ege/keyboard/listener.hxx>

namespace ege
{
    namespace keyboard
    {
        /**
         * \brief An abstraction of the keyboard.
         * */
        class Keyboard
        {
            public:
                virtual ~Keyboard() {};

                /**
                 * \brief Tells if a keyboard's key is pressed.
                 * \param key The key to check.
                 * \return \c True if key is pressed.
                 * */
                virtual bool isPressed(Key key) const = 0;

                /**
                 * \brief Add an EventListener to \c this keyboard.
                 * \param listener The listener to add.
                 * */
                virtual void addListener(Listener* listener) = 0;

                /**
                 * \brief Remove an EventListener to \c this keyboard.
                 * \param listener The listener to remove.
                 * */
                virtual void removeListener(Listener* listener) = 0;
        };
    }
}


#endif
