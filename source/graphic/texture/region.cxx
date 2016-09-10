#include <ege/graphic/texture/region.hxx>


using namespace ege::graphic;
using namespace ege::graphic::texture;


Region::Region( gpu::Texture &texture ): texture( texture )
{

}


gpu::Texture& Region::getTexture()
{
        return texture;
}
