
#ifndef EGE_FLOW_UPDATEABLE_HXX
#define EGE_FLOW_UPDATEABLE_HXX

#include <cstddef>
#include <memory>
#include <set>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Represent an updateable.
         * \sa Updateable::update()
         *
         * An updateable can have dependencies that have to be updated before the updateable.
         * */
        class Updateable
        {
            private:
                /**
                 * \brief The dependencies of \c this updateable.
                 * */
                std::set<std::shared_ptr<Updateable>> dependencies;

                /**
                 * \brief Check if a dependency creates a cycle with the existing ones.
                 * \param dependency The new dependency.
                 * \return \c True if a cycle is found.
                 * */
                bool cycleDetected(std::shared_ptr<Updateable> const& dependency) const;

            protected:
                /**
                 * \brief Update the \c this Updateable object.
                 * \param delta The time elapsed from the last update.
                 * \sa update()
                 *
                 * This method will be automatically called by the update() method.
                 * Default implementation is an empty function.
                 * */
                virtual void performUpdate(float delta);

            public:
                /**
                 * \brief Create the Updateable.
                 * */
                Updateable();

                virtual ~Updateable();

                /**
                 * \brief Tells if \c this is updated.
                 * \return \c True if it's updated.
                 * Default implementation returns \c false.
                 * */
                virtual bool isUpdated();

                /**
                 * \brief Update \c this updateable.
                 * \param delta The time elapsed from the last update.
                 *
                 * The implementation will firstly check if \c this is updated via isUpdated() method.
                 * If it's not: all dependencies will be recursively updated and the performUpdate() method
                 * is invoked. \n
                 * Implementation code:
                 * \code
                 * if (isUpdated())
                 *     return;
                 *
                 * for (auto& dependency : dependencies)
                 *     dependency->update(delta);
                 *
                 * performUpdate(delta);
                 * \endcode
                 * */
                void update(float delta);

                /**
                 * \brief Add a dependency to the updateable's dependencies set.
                 * \param updateable The dependency to add.
                 * \throws ege::Exception If a cycle is detected in the dependencies tree.
                 * */
                void addDependency(std::shared_ptr<Updateable> updateable);

                /**
                 * \brief Remove a dependency to the updateable's dependencies set.
                 * \param updateable The dependency to remove.
                 * */
                void removeDependency(std::shared_ptr<Updateable> updateable);

                /**
                 * \brief Remove all dependencies from the updateable's dependencies set.
                 * */
                void removeAllDependencies();

                /**
                 * \brief Return the number of directly accessible dependencies of \c this updateable.
                 * \return The number of direct dependencies.
                 * \sa getRecursiveDependenciesCount()
                 *
                 * This method doesn't count the sub dependencies, but only the ones that are directly
                 * stored in the updateable's dependencies set. Complexity: O(1).
                 * */
                std::size_t getDirectDependenciesCount() const;

                /**
                 * \brief Return the number of (all) dependencies in the dependency tree of \c this updateable.
                 * \return The number of dependencies.
                 *
                 * The method will recursively calculate the count, so it can be an expensive operation. Complexity:
                 * O(n), where n is the number of dependencies in dependency tree.
                 * */
                std::size_t getRecursiveDependenciesCount() const;
        };
    }
}

#endif
