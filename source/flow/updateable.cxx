#include <ege/flow/updateable.hxx>
#include <ege/exception.hxx>

namespace ege
{
    namespace flow
    {
        bool Updateable::cycleDetected(std::shared_ptr<Updateable> const& dependency) const
        {
            if (this == dependency.get())
                return true;

            for (auto& deeper : dependency->dependencies)
            {
                if (cycleDetected(deeper))
                    return true;
            }

            return false;
        }

        void Updateable::performUpdate(float delta)
        {

        }

        Updateable::Updateable()
        {

        }

        Updateable::~Updateable()
        {
            removeAllDependencies();
        }

        bool Updateable::isUpdated()
        {
            return false;
        }

        void Updateable::update(float delta)
        {
            if (isUpdated())
                return;

            for (auto& dependency : dependencies)
                dependency->update(delta);

            performUpdate(delta);
        }

        void Updateable::addDependency(std::shared_ptr<Updateable> updateable)
        {
            if (cycleDetected(updateable))
                ege::exception::throwNew("cycle detected in updateable dependencies");

            dependencies.insert(updateable);
        }

        void Updateable::removeDependency(std::shared_ptr<Updateable> updateable)
        {
            dependencies.erase(updateable);
        }

        void Updateable::removeAllDependencies()
        {
            dependencies.clear();
        }

        std::size_t Updateable::getDirectDependenciesCount() const
        {
            return dependencies.size();
        }
        
        std::size_t Updateable::getRecursiveDependenciesCount() const
        {
            std::size_t sum = getDirectDependenciesCount();

            for (auto& dependency : dependencies)
                sum += dependency->getRecursiveDependenciesCount();

            return sum;
        }
    }
}
