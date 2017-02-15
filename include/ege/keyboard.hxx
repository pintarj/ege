
#ifndef EGE_KEYBOARD_HXX
#define EGE_KEYBOARD_HXX

namespace ege
{
    namespace keyboard
    {
        /**
         * \brief The enumeration of keyboard's keys.
         * */
        enum class Key: unsigned int
        {
            SPACE           = 32,
            APOSTROPHE      = 39,
            COMMA           = 44,
            MINUS           = 45,
            PERIOD          = 46,
            SLASH           = 47,
            NUM_0           = 48,
            NUM_1           = 49,
            NUM_2           = 50,
            NUM_3           = 51,
            NUM_4           = 52,
            NUM_5           = 53,
            NUM_6           = 54,
            NUM_7           = 55,
            NUM_8           = 56,
            NUM_9           = 57,
            SEMICOLON       = 59,
            EQUAL           = 61,
            A               = 65,
            B               = 66,
            C               = 67,
            D               = 68,
            E               = 69,
            F               = 70,
            G               = 71,
            H               = 72,
            I               = 73,
            J               = 74,
            K               = 75,
            L               = 76,
            M               = 77,
            N               = 78,
            O               = 79,
            P               = 80,
            Q               = 81,
            R               = 82,
            S               = 83,
            T               = 84,
            U               = 85,
            V               = 86,
            W               = 87,
            X               = 88,
            Y               = 89,
            Z               = 90,
            LEFT_BRACKET    = 91,
            BACKSLASH       = 92,
            RIGHT_BRACKET   = 93,
            GRAVE_ACCENT    = 96,
            WORLD_1         = 161,
            WORLD_2         = 162,
            ESCAPE          = 256,
            ENTER           = 257,
            TAB             = 258,
            BACKSPACE       = 259,
            INSERT          = 260,
            DELETE          = 261,
            RIGHT           = 262,
            LEFT            = 263,
            DOWN            = 264,
            UP              = 265,
            PAGE_UP         = 266,
            PAGE_DOWN       = 267,
            HOME            = 268,
            END             = 269,
            CAPS_LOCK       = 280,
            SCROLL_LOCK     = 281,
            NUM_LOCK        = 282,
            PRINT_SCREEN    = 283,
            PAUSE           = 284,
            F1              = 290,
            F2              = 291,
            F3              = 292,
            F4              = 293,
            F5              = 294,
            F6              = 295,
            F7              = 296,
            F8              = 297,
            F9              = 298,
            F10             = 299,
            F11             = 300,
            F12             = 301,
            F13             = 302,
            F14             = 303,
            F15             = 304,
            F16             = 305,
            F17             = 306,
            F18             = 307,
            F19             = 308,
            F20             = 309,
            F21             = 310,
            F22             = 311,
            F23             = 312,
            F24             = 313,
            F25             = 314,
            KP_0            = 320,
            KP_1            = 321,
            KP_2            = 322,
            KP_3            = 323,
            KP_4            = 324,
            KP_5            = 325,
            KP_6            = 326,
            KP_7            = 327,
            KP_8            = 328,
            KP_9            = 329,
            KP_DECIMAL      = 330,
            KP_DIVIDE       = 331,
            KP_MULTIPLY     = 332,
            KP_SUBTRACT     = 333,
            KP_ADD          = 334,
            KP_ENTER        = 335,
            KP_EQUAL        = 336,
            LEFT_SHIFT      = 340,
            LEFT_CONTROL    = 341,
            LEFT_ALT        = 342,
            LEFT_SUPER      = 343,
            RIGHT_SHIFT     = 344,
            RIGHT_CONTROL   = 345,
            RIGHT_ALT       = 346,
            RIGHT_SUPER     = 347,
            MENU            = 348
        };

        /**
         * \brief The keyboard's key modifier.
         * */
        class Modifier
        {
            private:
                /**
                 * \brief The raw modifier value.
                 * */
                const unsigned int modifier;

            public:
                /**
                 * \brief Creates a Modifier.
                 * \param modifier The raw value.
                 * */
                Modifier(unsigned int modifier):
                    modifier(modifier)
                {

                }

                /**
                 * \brief Tells if "shift" is pressed.
                 * \return \c True if it's pressed.
                 * */
                inline bool isShift() const noexcept
                {
                    return (modifier & 0x1) != 0;
                }

                /**
                 * \brief Tells if "ctrl" is pressed.
                 * \return \c True if it's pressed.
                 * */
                inline bool isCtrl() const noexcept
                {
                    return (modifier & 0x2) != 0;
                }

                /**
                 * \brief Tells if "alt" is pressed.
                 * \return \c True if it's pressed.
                 */
                inline bool isAlt() const noexcept
                {
                    return (modifier & 0x4) != 0;
                }

                /**
                 * \brief Tells if "super" is pressed.
                 * \return \c True if it's pressed.
                 * */
                inline bool isSuper() const noexcept
                {
                    return (modifier & 0x8) != 0;
                }
        };

        /**
         * \brief The keyboard key (press/release) event listener.
         * */
        class EventListener
        {
            public:
                virtual ~EventListener() {}

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
                virtual void addEventListener(EventListener* listener) = 0;

                /**
                 * \brief Remove an EventListener to \c this keyboard.
                 * \param listener The listener to remove.
                 * */
                virtual void removeEventListener(EventListener* listener) = 0;
        };
    }
}


#endif
