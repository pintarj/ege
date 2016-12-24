

#ifndef EGE_GAME_UPDATEABLE_HXX
#define EGE_GAME_UPDATEABLE_HXX


#include <cstddef>
#include <memory>
#include <set>


namespace ege
{
        namespace game
        {
                class Updateable
                {
                        private:
                                std::set< std::shared_ptr< Updateable > > dependencies;

                                bool cycleDetected( std::shared_ptr< Updateable > const& dependency ) const;

                        protected:
                                virtual void performUpdate( float delta );

                        public:
                                Updateable();
                                virtual ~Updateable();
                                virtual bool isUpdated();
                                void update( float delta );
                                void addDependency( std::shared_ptr< Updateable > updateable );
                                void removeDependency( std::shared_ptr< Updateable > updateable );
                                void removeAllDependencies();
                                std::size_t getDirectDependenciesCount() const;
                                std::size_t getRecursiveDependenciesCount() const;

                };
        }
}


#endif
