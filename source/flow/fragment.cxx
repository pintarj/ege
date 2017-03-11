#include <ege/flow/fragment.hxx>
#include <algorithm>
#include <ege/exception.hxx>
#include <ege/engine/resources.hxx>

namespace ege
{
    namespace flow
    {
        static Fragment::Id nextId = 1;

        void Fragment::onDependencyUpdate(const Frame& frame)
        {
            --outDatedDependenciesCounter;

            if (outDatedDependenciesCounter == 0)
            {
                auto executable = [this, &frame]()
                    {
                        this->performUpdate(frame);
                        this->decreaseDependencyOfCounters(frame);
                    };

                if (requiresUpdateExecutionOnGraphicThread())
                    engine::getGraphicExecutor().execute(executable);
                else
                    // TODO This should be replaced by centralized parallel execution.
                    engine::getGraphicExecutor().execute(executable);
            }
        }

        void Fragment::decreaseDependencyOfCounters(const Frame& frame)
        {
            for (Fragment* fragment : dependencyOf)
                fragment->onDependencyUpdate(frame);
        }

        void Fragment::performUpdate(const Frame& frame)
        {

        }

        Fragment::Fragment():
            lastUpdatedFor(0),
            id(nextId++)
        {

        }

        void Fragment::addDependency(std::shared_ptr<Fragment> dependency)
        {
            dependency->dependencyOf.insert(this);
            dependencies.insert(dependency);
        }

        void Fragment::removeDependency(std::shared_ptr<Fragment> dependency)
        {
            dependency->dependencyOf.erase(this);
            dependencies.erase(dependency);
        }

        bool Fragment::isUpdated()
        {
            return false;
        }

        void Fragment::update(const Frame& frame)
        {
            if (lastUpdatedFor == frame.id)
                return;

            if (!isUpdated())
            {
                if (isLeaf())
                {
                    auto executable = [this, &frame]()
                        {
                            this->performUpdate(frame);
                            this->decreaseDependencyOfCounters(frame);
                        };

                    // TODO This should be replaced by centralized parallel execution.
                    engine::getGraphicExecutor().execute(executable);
                }
                else
                {
                    outDatedDependenciesCounter = (unsigned) dependencies.size();

                    for (auto& dependency : dependencies)
                        dependency->update(frame);
                }
            }

            lastUpdatedFor = frame.id;
        }

        bool Fragment::requiresUpdateExecutionOnGraphicThread() const
        {
            return true;
        }

        bool Fragment::isLeaf() const
        {
            return dependencies.empty();
        }
    }
}
