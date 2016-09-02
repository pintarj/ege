

#ifndef EGE_GRAPHIC_TEXTURE_TEXTURE_HXX
#define EGE_GRAPHIC_TEXTURE_TEXTURE_HXX


#include <ege/graphic/render/targetable.hxx>


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

                                public:
                                        Texture( size_t width, size_t height, const void* pixels = nullptr );
                                        size_t getTextureId();
                                        virtual ~Texture();

                                        void getDimensions( size_t* width, size_t* height );
                                        size_t getFrameBufferId();
                        };
                }
        }
}


#endif
