

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
                                        virtual ~Texture2D();
                        };
                }
        }
}


#endif
