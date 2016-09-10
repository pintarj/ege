

#ifndef EGE_GRAPHIC_GPU_TEXTURE_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_HXX


#include <ege/graphic/render/targetable.hxx>
#include <ege/graphic/texture/pixels-buffer.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Texture: public render::Targetable
                        {
                                private:
                                        size_t textureId;
                                        size_t width;
                                        size_t height;
                                        size_t frameBufferId;
                                        texture::Format format;

                                        Texture( texture::Format format );

                                public:
                                        Texture( texture::PixelsBuffer& pixelsBuffer, bool deleteBuffer = false );
                                        Texture( size_t width, size_t height, const void* pixels, texture::Format format = texture::Format::RGBA );
                                        Texture( size_t width, size_t height, texture::Format format = texture::Format::RGBA, bool willBeTargeted = true );
                                        size_t getTextureId();
                                        virtual ~Texture();
                                        void resize( size_t width, size_t height );
                                        void resize( size_t width, size_t height, size_t x, size_t y );
                                        void useAtUnit( size_t unit );
                                        texture::Format getFormat();
                                        void prepareForTargeting();
                                        size_t getWidth();
                                        size_t getHeight();
                                        void getDimensions( size_t* width, size_t* height );
                                        size_t getFrameBufferId();
                        };
                }
        }
}


#endif
