#include <ege/graphic/texture/region.hxx>


using namespace ege::graphic::texture;


Region::Region( Texture &texture ): texture( texture )
{

}


Texture& Region::getTexture()
{
        return texture;
}
