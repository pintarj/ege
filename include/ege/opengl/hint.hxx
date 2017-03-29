
#ifndef EGE_OPENGL_HINT_HXX
#define EGE_OPENGL_HINT_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumerate hint targets.
         * */
        enum class HintTarget: unsigned
        {
            LINE_SMOOTH                 = 0x0C52,
            POLYGON_SMOOTH              = 0x0C53,
            TEXTURE_COMPRESSION         = 0x84EF,
            FRAGMENT_SHADER_DERIVATIVE  = 0x8B8B
        };

        /**
         * \brief Enumerate hint behaviours.
         * */
        enum class Hint: unsigned
        {
            FASTEST     = 0x1101,
            NICEST      = 0x1102,
            DONT_CARE   = 0x1100
        };

        /**
         * \brief Specify implementation-specific hints.
         * \param target Specifies the behavior to be controlled.
         * \param hint Specifies the desired behavior.
         * */
        void setHint(HintTarget target, Hint hint) noexcept;
    }
}

#endif
