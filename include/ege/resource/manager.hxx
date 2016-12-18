

#ifndef EGE_RESOURCE_MANAGER_HXX
#define EGE_RESOURCE_MANAGER_HXX


#include <map>
#include <memory>
#include <set>
#include <ege/resource/factory.hxx>


namespace ege
{
        namespace resource
        {
                template < typename K, typename R, typename C = std::less< K > >
                class Manager
                {
                        private:
                                Factory< K, R >& factory;
                                std::map< K, std::pair< std::shared_ptr< R >, bool >, C >* resources;

                        public:
                                Manager( Factory< K, R >& factory );
                                virtual ~Manager();
                                void requireOnly( std::set< K > const& keys );
                                void requireOnlyUnloadOthers( std::set< K > const& keys );
                                void require( std::set< K > const& keys );
                                void dismiss( std::set< K > const& keys );
                                void dismissAll();
                                void unloadNotRequired();
                                void unloadAll();
                                bool isLoaded( K const& key ) const;
                                std::shared_ptr< R > get( K const& key ) const;
                                std::shared_ptr< R > operator [] ( K const& key ) const;
                };
        }
}


#include "manager.txx"


#endif
