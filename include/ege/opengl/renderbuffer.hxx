
#ifndef EGE_OPENGL_RENDERBUFFER_HXX
#define EGE_OPENGL_RENDERBUFFER_HXX

#include <ege/opengl/object.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumeration of possible renderbuffer internal formats.
         * */
        enum class RenderbufferInternalFormat: unsigned int
        {
            R8                  = 0x8229,
            R8UI                = 0x8232,
            R8I                 = 0x8231,
            R16UI               = 0x8234,
            R16I                = 0x8233,
            R32UI               = 0x8236,
            R32I                = 0x8235,
            RG8                 = 0x822B,
            RG8UI               = 0x8238,
            RG8I                = 0x8237,
            RG16UI              = 0x823A,
            RG16I               = 0x8239,
            RG32UI              = 0x823C,
            RG32I               = 0x823B,
            RGB8                = 0x8051,
            RGB565              = 0x8D62,
            RGBA8               = 0x8058,
            SRGB8_ALPHA8        = 0x8C43,
            RGB5_A1             = 0x8057,
            RGBA4               = 0x8056,
            RGB10_A2            = 0x8059,
            RGBA8UI             = 0x8D7C,
            RGBA8I              = 0x8D8E,
            RGB10_A2UI          = 0x906F,
            RGBA16UI            = 0x8D76,
            RGBA16I             = 0x8D88,
            RGBA32UI            = 0x8D70,
            RGBA32I             = 0x8D82,
            DEPTH_COMPONENT16   = 0x81A5,
            DEPTH_COMPONENT24   = 0x81A6,
            DEPTH_COMPONENT32F  = 0x8CAC,
            DEPTH24_STENCIL8    = 0x88F0,
            DEPTH32F_STENCIL8   = 0x8CAD,
            STENCIL_INDEX8      = 0x8D48
        };

        /**
         * \brief Wrapper for the OpenGL renderbuffer object.
         *
         * Renderbuffer objects are non movable and non copyable.
         * */
        class Renderbuffer: public Object<unsigned int>
        {
            public:
                /**
                 * \brief The width of the renderbuffer.
                 * */
                const int width;

                /**
                 * \brief The height of the renderbuffer.
                 * */
                const int height;

                /**
                 * \brief Create a Renderbuffer object with the specified width, height, internal format.
                 * \param width Specifies the width of the renderbuffer, in pixels.
                 * \param height Specifies the height of the renderbuffer, in pixels.
                 * \param internalFormat Specifies the internal format to use for the renderbuffer object's image.
                 * \param samples Specifies the number of samples to be used.
                 * Optionally the number of samples can be specified.
                 * */
                Renderbuffer(int width, int height, RenderbufferInternalFormat internalFormat, int samples = 0);

                Renderbuffer(Renderbuffer&&) = delete;
                Renderbuffer(const Renderbuffer&) = delete;
                virtual ~Renderbuffer();
        };
    }
}

#endif
