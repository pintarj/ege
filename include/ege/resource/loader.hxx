
#ifndef EGE_LOADER_HXX
#define EGE_LOADER_HXX


#include <memory>


namespace ege
{
        namespace resource
        {
                template < typename R >
                class Loader
                {
                        public:
                                virtual ~Loader() {};
                                virtual void completeUpTo( double level ) = 0;
                                virtual double getCompletion() const = 0;
                                void complete() { completeUpTo( 1.0 ); };
                                bool isCompleted() const { return getCompletion() == 1.0; };
                                virtual std::shared_ptr< R > getResource() const = 0;
                };
        }
}


#endif
