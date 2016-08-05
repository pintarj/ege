

#ifndef EGE_RESOURCE_MANAGER_HXX
#define EGE_RESOURCE_MANAGER_HXX


#include <ege/resource/resource.hxx>
#include <map>
#include <string>


namespace ege
{
        namespace resource
        {
                class Manager
                {
                        private:
                                char* resourcesRootPath;
                                std::map< std::string, Resource* > resources[ numberOfTypes ];

                        public:
                                Manager( const char* resourcesRootPath );
                                virtual ~Manager();
                                Resource* getResource( Type type, const char* idString );
                };
        }
}


#endif
