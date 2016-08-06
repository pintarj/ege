#include <ege/resource/resource.hxx>


using namespace ege::resource;


Resource::Resource( const char* idString, Type type ): idString( idString ), type( type )
{
        numberOfUsers = 0;
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


void Resource::addAnUser()
{
        ++numberOfUsers;
}


void Resource::removeAnUser()
{
        --numberOfUsers;
}


size_t Resource::getNumberOfUsers()
{
        return numberOfUsers;
}
