
#ifndef EGE_OPENGL_FRAMEBUFFER_HXX
#define EGE_OPENGL_FRAMEBUFFER_HXX

#include <ege/opengl/object.hxx>
#include <ege/opengl/renderbuffer.hxx>
#include <ege/opengl/sampler.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief The framebuffer attachment points enumeration.
         * */
        enum class FramebufferAttachment: unsigned int
        {
            COLOR0          = 0x8CE0,
            DEPTH           = 0x8D00,
            STENCIL         = 0x8D20,
            DEPTH_STENCIL   = 0x821A
        };

        /**
         * \brief An alias for the FramebufferAttachment.
         * */
        using FBOAttachment = FramebufferAttachment;

        /**
         * \brief Calculate the addition value of a FramebufferAttachment and an \c int.
         * */
        static inline constexpr FBOAttachment operator+(FBOAttachment attachment, unsigned int index)
        {
            return (FBOAttachment) ((unsigned int) attachment + index);
        }

        /**
         * \brief The framebuffer buffer enumerations.
         * */
        enum class FramebufferBuffer: unsigned int
        {
            COLOR   = 0x00004000,
            DEPTH   = 0x00000100,
            STENCIL = 0x00000400
        };

        /**
         * \brief An alias for the FramebufferBuffer.
         * */
        using FBOBuffer = FramebufferBuffer;

        /**
         * \brief Calculate the bitwise value of the two FBOBuffer parameters.
         * */
        static inline constexpr FBOBuffer operator|(FBOBuffer left, FBOBuffer right)
        {
            return (FBOBuffer) ((unsigned int) left | (unsigned int) right);
        }

        /**
         * \brief Calculate the bitwise value of the two FBOBuffer parameters.
         * */
        static inline constexpr FBOBuffer& operator|=(FBOBuffer& left, FBOBuffer right)
        {
            left = left | right;
            return left;
        }

        /**
         * \brief Wrapper for the OpenGL framebuffer object.
         *
         * Framebuffer objects are non movable and non copyable.
         * */
        class Framebuffer: public Object<unsigned int>
        {
            protected:
                /**
                 * \brief Create a framebuffer wrapper with a given id.
                 * */
                Framebuffer(unsigned int id);

            public:
                /**
                 * Create a framebuffer.
                 * \sa Framebuffer::attachRenderbuffer()
                 * */
                Framebuffer();

                Framebuffer(Framebuffer&&) = delete;
                Framebuffer(const Framebuffer&) = delete;
                virtual ~Framebuffer();

                /**
                 * \brief Bind the framebuffer.
                 *
                 * It binds framebuffer to GL_FRAMEBUFFER.
                 * */
                void bind() const;

                /**
                 * \brief Attach a renderbuffer as a logical buffer of \c this.
                 * \param attachment Specifies the attachment point of the framebuffer.
                 * \param renderbuffer Specifies the renderbuffer to attach.
                 *
                 * Referenced OpenGL function: glNamedFramebufferRenderbuffer
                 * */
                void attachRenderbuffer(FBOAttachment attachment, Renderbuffer& renderbuffer);

                /**
                 * \brief Tells if \c this is the default framebuffer.
                 * \return \c true if it's the default framebuffer, \c false otherwise.
                 * */
                bool isDefault() const;

                /**
                 * \brief Clear the color buffers of \c this framebuffer.
                 * \param index Index of the specific draw buffer.
                 * \param values Four-element float vector specifying the R, G, B and A color to clear
                 *      that draw buffer to.
                 *
                 * Referenced OpenGL function: glClearNamedFramebufferfv
                 * */
                void clearColor(unsigned index, const float* values);

                /**
                 * \brief Clear the color buffers of \c this framebuffer.
                 * \param index Index of the specific draw buffer.
                 * \param r The red component.
                 * \param g The green component.
                 * \param b The blue component.
                 * \param a The alpha component. The default is 0.0f.
                 *
                 * Referenced OpenGL function: glClearNamedFramebufferfv
                 * */
                void clearColor(unsigned index, float r, float g, float b, float a = 0.0f);

                /**
                 * \brief Clear the depth buffers of \c this framebuffer.
                 * \param depth Value to clear the depth buffer to.
                 *
                 * Referenced OpenGL function: glClearNamedFramebufferfv
                 * */
                void clearDepth(float depth = 1.0f);

                /**
                 * \brief Clear the stencil buffers of \c this framebuffer.
                 * \param stencil Value to clear the stencil buffer to.
                 *
                 * Referenced OpenGL function: glClearNamedFramebufferiv
                 * */
                void clearStencil(int stencil = 0);

                /**
                 * \brief Invalidate the content of a framebuffer's attachments.
                 * \param attachment The attachment to invalidate.
                 *
                 * Referenced OpenGL function: glInvalidateNamedFramebufferData
                 * */
                void invalidate(FramebufferAttachment attachment);

                /**
                 *
                 * Referenced OpenGL function: glBlitNamedFramebuffer
                 * */
                void blitFrom(const Framebuffer& source, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0,
                    int dstX1, int dstY1, FBOBuffer target, Filter filter);
        };

        /**
         * \brief An alias for the Framebuffer.
         * */
        using FBO = Framebuffer;

        /**
         * \brief Clear buffers of the current bound framebuffer to preset values.
         * \param target The bitwise combination of target buffer to be cleared. Default parameter are all
         *               three targets combined.
         * */
        void clear(FBOBuffer target = FBOBuffer::COLOR | FBOBuffer::DEPTH | FBOBuffer::STENCIL);

        /**
         * \brief Specify clear values for the color buffers.
         * \param r The red component.
         * \param g The green component.
         * \param b The blue component.
         * \param a The alpha component. The default is 0.0f.
         * */
        void setClearColor(float r, float g, float b, float a = 0.0f);

        /**
         * \brief Specify the clear value for the depth buffer.
         * \param d Specifies the depth value used when the depth buffer is cleared.
         * */
        void setClearDepth(float d);

        /**
         * \brief Specify the clear value for the stencil buffer.
         * \param s Specifies the index used when the stencil buffer is cleared.
         * */
        void setClearStencil(int s);
    }
}

#endif
