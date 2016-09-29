

#ifndef EGE_GRAPHIC_GPU_TEXTURE_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_HXX


#include <ege/graphic/gpu/object.hxx>
#include <ege/graphic/gpu/texture/format.hxx>
#include <ege/graphic/gpu/texture/type.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Texture: public Object
                        {
                                protected:
                                        const texture::Format format;
                                        Texture( texture::Type type, texture::Format format );

                                public:
                                        const texture::Type type;

                                        virtual ~Texture();
                                        void bindAtUnit( unsigned int index ) const;
                        };
                }
        }
}


#endif
