
#ifndef EGE_KEYBOARD_LISTENER_HXX
#define EGE_KEYBOARD_LISTENER_HXX

#include <ege/keyboard/modifier.hxx>
#include <ege/keyboard/key.hxx>

namespace ege
{
    namespace keyboard
    {
        /**
         * \brief The keyboard key (press/release) event listener.
         * */
        class Listener
        {
            public:
                virtual ~Listener() {}

                /**
                 * \brief Called when a key is pressed.
                 * \param key The key that is pressed.
                 * \param modifier The current modifier.
                 * */
                virtual void onKeyPress(Key key, const Modifier modifier) {}

                /**
                 * \brief Called when a key is released.
                 * \param key The key that is pressed.
                 * \param modifier The current modifier.
                 * */
                virtual void onKeyRelease(Key key, const Modifier modifier) {}
        };
    }
}

#endif
