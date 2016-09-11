#include <ege/graphic/texture/region.hxx>


using namespace ege::graphic;
using namespace ege::graphic::texture;


Region::Region( gpu::Texture2D &texture ): texture( texture )
{

}


gpu::Texture2D& Region::getTexture()
{
        return texture;
}
