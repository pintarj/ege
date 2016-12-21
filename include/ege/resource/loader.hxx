
#ifndef EGE_LOADER_HXX
#define EGE_LOADER_HXX


#include <chrono>
#include <memory>
#include <functional>
#include <future>


namespace ege
{
        namespace resource
        {
                template < typename R >
                class Loader
                {
                        public:
                                virtual ~Loader() {};
                                virtual void complete( std::function< void() > const& callback = [] () {} ) = 0;
                                virtual std::future< void > asyncComplete( std::function< void() > const& callback = [] () {} );
                                virtual double getCompletion() const = 0;
                                virtual bool isCompleted() const;
                                virtual std::shared_ptr< R > getResource() const = 0;
                };
        }
}


#include "loader.txx"


#endif
