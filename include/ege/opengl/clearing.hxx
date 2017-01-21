
#ifndef EGE_OPENGL_CLEARING_HXX
#define EGE_OPENGL_CLEARING_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumeration of clear targets.
         * \sa ege::opengl::clear()
         *
         * They can be combined bit-wisely.
         * */
        enum class ClearTarget
        {
            COLOR   = 0x00004000,
            DEPTH   = 0x00000100,
            STENCIL = 0x00000400
        };

        /**
         * \brief Calculate the bitwise value of the two ClearTarget parameters.
         * */
        static inline constexpr ClearTarget operator|(ClearTarget left, ClearTarget right)
        {
            return (ClearTarget) ((unsigned int) left | (unsigned int) right);
        }

        /**
         * \brief Calculate the bitwise value of the two ClearTarget parameters.
         * */
        static inline constexpr ClearTarget& operator|=(ClearTarget& left, ClearTarget right)
        {
            left = left | right;
            return left;
        }

        /**
         * \brief Clear buffers to preset values.
         * \param target The bitwise combination of target buffer to be cleared. Default parameter are all
         *               three target combined.
         * */
        void clear(ClearTarget target = ClearTarget::COLOR | ClearTarget::DEPTH | ClearTarget::STENCIL);

        /**
         * \brief Specify clear values for the color buffers.
         * \param r The red component.
         * \param g The green component.
         * \param b The blue component.
         * \param a The alpha component.
         * */
        void setClearColor(float r, float g, float b, float a);

        /**
         * \brief Specify the clear value for the depth buffer.
         * \param d Specifies the depth value used when the depth buffer is cleared.
         * */
        void setClearDepth(float d);

        /**
         * \brief Specify the clear value for the depth buffer.
         * \param d Specifies the depth value used when the depth buffer is cleared.
         * */
        void setClearDepth(double d);

        /**
         * \brief Specify the clear value for the stencil buffer.
         * \param s Specifies the index used when the stencil buffer is cleared.
         * */
        void setClearStencil(int s);
    }
}

#endif
