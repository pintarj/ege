

#ifndef EGE_GRAPHIC_TEXTURE_REGION_HXX
#define EGE_GRAPHIC_TEXTURE_REGION_HXX


#include <ege/graphic/gpu/texture-2D.hxx>


namespace ege
{
        namespace graphic
        {
                namespace texture
                {
                        class Region
                        {
                                protected:
                                        gpu::Texture2D& texture;
                                        Region( gpu::Texture2D& texture );

                                public:
                                        virtual ~Region() {};
                                        gpu::Texture2D& getTexture();
                        };
                }
        }
}


#endif
