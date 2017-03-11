#include <ege/flow/fragment.hxx>
#include <algorithm>
#include <ege/exception.hxx>

namespace ege
{
    namespace flow
    {
        static Fragment::Id nextId = 1;

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
            dependencies.insert(dependency);
        }

        void Fragment::removeDependency(std::shared_ptr<Fragment> dependency)
        {
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
                for (auto& dependency : dependencies)
                    dependency->update(frame);

                performUpdate(frame);
            }

            lastUpdatedFor = frame.id;
        }

        bool Fragment::requiresUpdateExecutionOnGraphicThread() const
        {
            return true;
        }
    }
}
