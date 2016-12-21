#include <algorithm>


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::moveLoadedResources()
{
        while ( loadedQueue.size() != 0 )
        {
                K& key = loadedQueue.front();
                auto i = loadings.find( key );
                auto inner = std::pair< std::shared_ptr< R >, bool >( i->second.first->getResource(), true );
                resources->insert( std::pair< K, std::pair< std::shared_ptr< R >, bool > >( key, inner ) );
                loadings.erase( i );
                loadedQueue.pop();
        }
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::startAsyncLoad()
{
        std::lock_guard< std::mutex > lock0( loadingMutex );

        if ( loading )
                return;

        loading = true;

        scheduler = std::async( std::launch::async, [ this ] ()
                {
                        {
                                std::lock_guard< std::mutex > lock( this->loadingMutex );
                        }

                        while ( true )
                        {
                                std::unique_lock< std::mutex > lock( this->loadingsMutex );

                                {
                                        std::lock_guard< std::mutex > lock( this->loadingQueueMutex );

                                        if ( this->loadingsQueue.size() == 0 )
                                                break;
                                }

                                loadingCompletedSignal.wait( lock, [ this ] ()
                                        {
                                                moveLoadedResources();
                                                return this->loadings.size() < this->maxParallelLoadings;
                                        } );

                                K* key = nullptr;

                                {
                                        std::lock_guard< std::mutex > lock( this->loadingQueueMutex );
                                        key = &this->loadingsQueue.front();
                                }

                                std::shared_ptr< ege::resource::Loader< R > > loader = factory.load( *key );

                                loadings[ *key ] = std::pair< std::shared_ptr< Loader< R > >, std::future< void > >( loader, loader->asyncComplete( [ this, key, loader ] ()
                                        {
                                                std::lock_guard< std::mutex > lock1( this->loadingsMutex );
                                                this->loadedQueue.push( *key );
                                                this->loadingCompletedSignal.notify_all();
                                        } ) );

                                {
                                        std::lock_guard< std::mutex > lock( this->loadingQueueMutex );
                                        this->loadingsQueue.pop();
                                }
                        }

                        {
                                std::unique_lock< std::mutex > lock( this->loadingsMutex );

                                this->loadingCompletedSignal.wait( lock, [ this ] ()
                                {
                                        moveLoadedResources();
                                        return this->loadings.size() == 0;
                                } );
                        }

                        {
                                std::lock_guard< std::mutex > lock( this->loadingMutex );
                                this->loading = false;
                                this->consistentStateSignal.notify_all();
                        }
                } );
}


template< typename K, typename R, typename C >
ege::resource::Manager< K, R, C >::Manager( ege::resource::Factory< K, R >& factory ):
        maxParallelLoadings( std::thread::hardware_concurrency() * 1 ),
        loading( false ),
        factory( factory ),
        resources( new std::map< K, std::pair< std::shared_ptr< R >, bool >, C >() )
{

}


template< typename K, typename R, typename C >
ege::resource::Manager< K, R, C >::~Manager()
{
        unloadAll();
        delete resources;
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::requireOnly( std::set< K > const& keys, bool async )
{
        dismissAll();
        require( keys, async );
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::requireOnlyUnloadOthers( std::set< K > const& keys, bool async )
{
        auto newResources = new std::map< K, std::pair< std::shared_ptr< R >, bool >, C >();

        for ( K const& key : keys )
        {
                auto i = resources->find( key );

                if ( i == resources->end() )
                        continue;

                newResources->insert( *i );
                resources->erase( i );
        }

        resources->clear();
        delete resources;
        resources = newResources;
        requireOnly( keys, async );
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::require( std::set< K > const& keys, bool async )
{
        for ( K const& key : keys )
        {
                auto i = resources->find( key );

                if ( i != resources->end() )
                {
                        i->second.second = true;
                        continue;
                }

                {
                        std::lock_guard< std::mutex > lock( loadingQueueMutex );
                        loadingsQueue.push( key );
                }
        }

        startAsyncLoad();

        if ( !async )
                waitConsistentState();
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::dismiss( std::set< K > const& keys )
{
        for ( K const& key : keys )
        {
                auto i = resources->find( key );

                if ( i == resources->end() )
                        continue;

                i->second.second = false;
        }
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::dismissAll()
{
        for ( auto i = resources->begin(); i != resources->end(); ++i )
                i->second.second = false;
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::unloadNotRequired()
{
        for ( auto i = resources->begin(); i != resources->end(); )
        {
                bool required = i->second.second;

                if ( !required )
                        i = resources->erase( i );
                else
                        ++i;
        }
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::unloadAll()
{
        dismissAll();
        unloadNotRequired();
}


template< typename K, typename R, typename C >
bool ege::resource::Manager< K, R, C >::isInConsistentState()
{
        std::lock_guard< std::mutex > lock( loadingMutex );
        return !loading;
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::waitConsistentState()
{
        std::unique_lock< std::mutex > lock( loadingMutex );
        consistentStateSignal.wait( lock, [ this ] () { return !loading; } );
}


template< typename K, typename R, typename C >
bool ege::resource::Manager< K, R, C >::isLoaded( K const& key ) const
{
        return resources->find( key ) != resources->end();
}


template< typename K, typename R, typename C >
std::shared_ptr< R > ege::resource::Manager< K, R, C >::get( K const& key ) const
{
        auto i = resources->find( key );

        if ( i == resources->end() )
                ege::Exception::throwNew( "trying to get an unloaded resource" );

        return i->second.first;
}


template< typename K, typename R, typename C >
std::shared_ptr< R > ege::resource::Manager< K, R, C >::operator [] ( K const& key ) const
{
        return get( key );
}
