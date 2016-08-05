#include <ege/resource/resource.hxx>


using namespace ege::resource;


Resource::Resource( const char* idString, Type type ): idString( idString ), type( type )
{

}


Resource::~Resource()
{

}


const char* Resource::getIdString()
{
        return idString;
}


const Type Resource::getType()
{
        return type;
}
