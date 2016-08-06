#include <ege/graphic/image.hxx>
#include <ege/engine/engine.hxx>


using namespace ege;
using namespace ege::graphic;


Image::Image( const char* idString )
{
        res = ( resource::Image* ) engine::resources.resourcesManager->getResource( resource::Type::IMAGE, idString );
        res->addAnUser();
}


Image::~Image()
{
        res->removeAnUser();
}
