#include <algorithm>


template< typename K, typename R, typename C >
ege::resource::Manager< K, R, C >::Manager( ege::resource::Factory< K, R >& factory ):
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
void ege::resource::Manager< K, R, C >::requireOnly( std::set< K > const& keys )
{
        dismissAll();
        require( keys );
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::requireOnlyUnloadOthers( std::set< K > const& keys )
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
        requireOnly( keys );
}


template< typename K, typename R, typename C >
void ege::resource::Manager< K, R, C >::require( std::set< K > const& keys )
{
        for ( K const& key : keys )
        {
                auto i = resources->find( key );

                if ( i != resources->end() )
                {
                        i->second.second = true;
                        continue;
                }

                std::shared_ptr< ege::resource::Loader< R > > loader = factory.load( key );
                loader->complete();
                auto inner = std::pair< std::shared_ptr< R >, bool >( loader->getResource(), true );
                resources->insert( std::pair< K, std::pair< std::shared_ptr< R >, bool > >( key, inner ) );
        }
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
