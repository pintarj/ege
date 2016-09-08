

#ifndef EGE_GRAPHIC_TEXTURE_REGION_HXX
#define EGE_GRAPHIC_TEXTURE_REGION_HXX


#include <ege/graphic/texture/texture.hxx>


namespace ege
{
        namespace graphic
        {
                namespace texture
                {
                        class Region
                        {
                                protected:
                                        Texture& texture;
                                        Region( Texture& texture );

                                public:
                                        virtual ~Region() {};
                                        Texture& getTexture();
                        };
                }
        }
}


#endif
