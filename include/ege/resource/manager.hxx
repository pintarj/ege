

#ifndef EGE_RESOURCE_MANAGER_HXX
#define EGE_RESOURCE_MANAGER_HXX


#include <ege/resource/resource.hxx>
#include <ege/resource/root.hxx>
#include <map>
#include <string>


namespace ege
{
        namespace resource
        {
                class Manager
                {
                        private:
                                Root* root;
                                std::map< std::string, Resource* > resources[ numberOfTypes ];

                        public:
                                Manager( Root* root );
                                virtual ~Manager();
                                Resource* getResource( Type type, const char* idString );
                };
        }
}


#endif
