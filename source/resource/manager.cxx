#include <ege/resource/manager.hxx>
#include <ege/resource/image.hxx>
#include <cstring>


using namespace ege::resource;


Manager::Manager( const char* resourcesRootPath )
{
        size_t len = std::strlen( resourcesRootPath );
        this->resourcesRootPath = new char[ len + 1 ];
        std::memcpy( this->resourcesRootPath, resourcesRootPath, len );
        this->resourcesRootPath[ len ] = '\0';
}


Manager::~Manager()
{
        delete resourcesRootPath;
}


Resource* Manager::getResource( Type type, const char* idString )
{
        std::map< std::string, Resource* >& map = resources[ ( size_t ) type ];
        auto iterator = map.find( idString );
        Resource* res;

        if ( iterator == map.end() )
        {
                switch ( type )
                {
                        case Type::IMAGE:
                                res = new Image( idString );
                                break;
                }

                map[ idString ] = res;
        }
        else
        {
                res = iterator->second;
        }

        return res;
}
