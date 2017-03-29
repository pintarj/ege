
#ifndef EGE_OPENGL_BLENDING_HXX
#define EGE_OPENGL_BLENDING_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumerates blend factors.
         * \sa setBlendFunction()
         * */
        enum class BlendFactor: unsigned
        {
            ZERO                        = 0x0000,
            ONE                         = 0x0001,
            SRC_COLOR                   = 0x0300,
            ONE_MINUS_SRC_COLOR         = 0x0301,
            DST_COLOR                   = 0x0306,
            ONE_MINUS_DST_COLOR         = 0x0307,
            SRC_ALPHA                   = 0x0302,
            ONE_MINUS_SRC_ALPHA         = 0x0303,
            DST_ALPHA                   = 0x0304,
            ONE_MINUS_DST_ALPHA         = 0x0305,
            CONSTANT_COLOR              = 0x8001,
            ONE_MINUS_CONSTANT_COLOR    = 0x8002,
            CONSTANT_ALPHA              = 0x8003,
            ONE_MINUS_CONSTANT_ALPHA    = 0x8004,
            SRC_ALPHA_SATURATE          = 0x0308
        };

        /**
         * \brief Enable blending.
         *
         * If blending is enabled, blend the computed fragment color
         * values with the values in the color buffers.
         * */
        void enableBlending() noexcept;

        /**
         * \brief Disable blending.
         * */
        void disableBlending() noexcept;

        /**
         * \brief Defines the operation of blending.
         * \param source Specifies which method is used to scale the source color components.
         * \param destination Specifies which method is used to scale the destination color components.
         * */
        void setBlendFunction(BlendFactor source, BlendFactor destination) noexcept;
    }
}

#endif
