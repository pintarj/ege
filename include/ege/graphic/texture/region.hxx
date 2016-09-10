

#ifndef EGE_GRAPHIC_TEXTURE_REGION_HXX
#define EGE_GRAPHIC_TEXTURE_REGION_HXX


#include <ege/graphic/gpu/texture.hxx>


namespace ege
{
        namespace graphic
        {
                namespace texture
                {
                        class Region
                        {
                                protected:
                                        gpu::Texture& texture;
                                        Region( gpu::Texture& texture );

                                public:
                                        virtual ~Region() {};
                                        gpu::Texture& getTexture();
                        };
                }
        }
}


#endif
