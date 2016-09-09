

#ifndef EGE_GRAPHIC_TEXTURE_TEXTURE_HXX
#define EGE_GRAPHIC_TEXTURE_TEXTURE_HXX


#include <ege/graphic/render/targetable.hxx>
#include <ege/graphic/texture/pixels-buffer.hxx>


namespace ege
{
        namespace graphic
        {
                namespace texture
                {
                        class Texture: public render::Targetable
                        {
                                private:
                                        size_t textureId;
                                        size_t width;
                                        size_t height;
                                        size_t frameBufferId;
                                        Format format;

                                        Texture( Format format );

                                public:
                                        Texture( PixelsBuffer& pixelsBuffer, bool deleteBuffer = false );
                                        Texture( size_t width, size_t height, const void* pixels, Format format = Format::RGBA );
                                        Texture( size_t width, size_t height, Format format = Format::RGBA, bool willBeTargeted = true );
                                        size_t getTextureId();
                                        virtual ~Texture();
                                        void useAtUnit( size_t unit );
                                        Format getFormat();
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
