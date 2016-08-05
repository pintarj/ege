#include <ege/resource/manager.hxx>
#include <ege/resource/image.hxx>
#include <cstring>


using namespace ege::resource;


Manager::Manager( Root* root ): root( root )
{

}


Manager::~Manager()
{

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
