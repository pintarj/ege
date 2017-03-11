
#ifndef EGE_KEYBOARD_MODIFIER_HXX
#define EGE_KEYBOARD_MODIFIER_HXX

namespace ege
{
    namespace keyboard
    {
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
    }
}

#endif
