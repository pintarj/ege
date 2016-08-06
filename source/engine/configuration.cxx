#include <ege/engine/configuration.hxx>


using namespace ege;
using namespace ege::engine;


static resource::Root localDir( "." );


Configuration::Configuration(): root( localDir )
{

}


Configuration::~Configuration()
{

}
