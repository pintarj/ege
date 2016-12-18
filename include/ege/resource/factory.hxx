

#ifndef EGE_RESOURCE_FACTORY_HXX
#define EGE_RESOURCE_FACTORY_HXX


#include <memory>
#include <ege/resource/loader.hxx>


namespace ege
{
        namespace resource
        {
                template < typename K, typename R >
                class Factory
                {
                        public:
                                virtual ~Factory() {};
                                virtual std::shared_ptr< Loader< R > > load( K const& key ) = 0;
                };
        }
}


#endif
