#include <ege/game/updateable.hxx>
#include <ege/exception.hxx>


bool ege::game::Updateable::cycleDetected( std::shared_ptr< Updateable > const& dependency ) const
{
        if ( this == dependency.get() )
                return true;

        for ( auto& deeper : dependency->dependencies )
        {
                if ( cycleDetected( deeper ) )
                        return true;
        }

        return false;
}


void ege::game::Updateable::performUpdate( float delta )
{

}


ege::game::Updateable::Updateable()
{

}


ege::game::Updateable::~Updateable()
{
        removeAllDependencies();
}


bool ege::game::Updateable::isUpdated()
{
        return false;
}


void ege::game::Updateable::update( float delta )
{
        if ( isUpdated() )
                return;

        for ( auto& dependency : dependencies )
                dependency->update( delta );

        performUpdate( delta );
}


void ege::game::Updateable::addDependency( std::shared_ptr< Updateable > updateable )
{
        if ( cycleDetected( updateable ) )
                ege::exception::throwNew( "cycle detected in updateable dependencies" );

        dependencies.insert( updateable );
}


void ege::game::Updateable::removeDependency( std::shared_ptr< Updateable > updateable )
{
        dependencies.erase( updateable );
}


void ege::game::Updateable::removeAllDependencies()
{
        dependencies.clear();
}


std::size_t ege::game::Updateable::getDirectDependenciesCount() const
{
        return dependencies.size();
}


std::size_t ege::game::Updateable::getRecursiveDependenciesCount() const
{
        std::size_t sum = getDirectDependenciesCount();

        for ( auto& dependency : dependencies )
                sum += dependency->getRecursiveDependenciesCount();

        return sum;
}
