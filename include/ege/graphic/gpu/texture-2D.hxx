

#ifndef EGE_TEXTURE_2D_HXX
#define EGE_TEXTURE_2D_HXX


#include <ege/graphic/gpu/texture.hxx>
#include <ege/graphic/gpu/util/image/buffer.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Texture2D: public Texture
                        {
                                public:
                                        const unsigned int width;
                                        const unsigned int height;

                                        Texture2D( const util::image::Buffer& imageBuffer, texture::Format format );
                                        Texture2D( const util::image::Buffer& imageBuffer );
                                        Texture2D( unsigned int width, unsigned int height, texture::Format format = texture::Format::RGBA );
                                        virtual ~Texture2D();
                                        void substitute( unsigned int x, unsigned int y, const util::image::Buffer& imageBuffer );
                        };
                }
        }
}


#endif
