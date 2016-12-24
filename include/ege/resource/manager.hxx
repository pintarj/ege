

#ifndef EGE_RESOURCE_MANAGER_HXX
#define EGE_RESOURCE_MANAGER_HXX


#include <map>
#include <memory>
#include <set>
#include <mutex>
#include <queue>
#include <ege/resource/factory.hxx>


namespace ege
{
        namespace resource
        {
                template < typename K, typename R, typename C = std::less< K > >
                class Manager
                {
                        private:
                                const unsigned maxParallelLoadings;
                                Factory< K, R >& factory;
                                std::map< K, std::pair< std::shared_ptr< R >, bool >, C >* resources;
                                std::queue< K > loadingsQueue;
                                std::map< K, std::pair< std::shared_ptr< Loader< R > >, std::future< void > >, C > loadings;
                                std::queue< K > loadedQueue;
                                std::mutex resourcesMutex;
                                std::mutex loadingMutex;
                                std::mutex loadingsMutex;
                                std::mutex loadingQueueMutex;
                                std::condition_variable loadingCompletedSignal;
                                std::condition_variable consistentStateSignal;
                                std::future< void > scheduler;
                                bool loading;

                                void moveLoadedResources();
                                void startAsyncLoad();

                        public:
                                Manager( Factory< K, R >& factory, unsigned threadsPerCore = 4 );
                                virtual ~Manager();
                                void requireOnly( std::set< K > const& keys, bool async = false );
                                void requireOnlyUnloadOthers( std::set< K > const& keys, bool async = false );
                                void require( std::set< K > const& keys, bool async = false );
                                void dismiss( std::set< K > const& keys );
                                void dismissAll();
                                void unloadNotRequired();
                                void unloadAll();
                                bool isInConsistentState();
                                void waitConsistentState();
                                bool isLoaded( K const& key );
                                std::shared_ptr< R > get( K const& key );
                                std::shared_ptr< R > operator [] ( K const& key );
                };
        }
}


#include "manager.txx"


#endif
