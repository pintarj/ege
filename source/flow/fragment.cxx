#include <ege/flow/fragment.hxx>
#include <algorithm>
#include <ege/exception.hxx>
#include <ege/flow/fragments-graph.hxx>

namespace ege
{
    namespace flow
    {
        class MegaFragmentsGraph: public FragmentsGraph
        {
            private:
                const Fragment* const origin;
                bool changedFlag;
                unsigned fragmentsCount;
                unsigned dependenciesCount;
                void changed() noexcept;

            public:
                MegaFragmentsGraph(const Fragment* origin);
                virtual ~MegaFragmentsGraph() {}
                virtual bool hasChanged() override;
                virtual unsigned getFragmentsCount() override;
                virtual unsigned getDependenciesCount() override;
                void merge(FragmentsGraph* other);
                bool isOrigin(const Fragment* fragment);
        };

        static Fragment::Id nextId = 1;

        void MegaFragmentsGraph::changed() noexcept
        {
            changedFlag = true;
        }

        MegaFragmentsGraph::MegaFragmentsGraph(const Fragment* origin):
            origin(origin),
            changedFlag(false),
            fragmentsCount(1),
            dependenciesCount(0)
        {

        }

        bool MegaFragmentsGraph::hasChanged()
        {
            if (!changedFlag)
                return false;

            changedFlag = false;
            return true;
        }

        unsigned MegaFragmentsGraph::getFragmentsCount()
        {
            return fragmentsCount;
        }

        unsigned MegaFragmentsGraph::getDependenciesCount()
        {
            return dependenciesCount;
        }

        void MegaFragmentsGraph::merge(FragmentsGraph* other)
        {
            if (((FragmentsGraph*) this) == other)
            {
                ++this->dependenciesCount;
            }
            else
            {
                this->fragmentsCount += other->getFragmentsCount();
                this->dependenciesCount += 1 + other->getDependenciesCount();
            }

            changed();
        }

        bool MegaFragmentsGraph::isOrigin(const Fragment* fragment)
        {
            return fragment == this->origin;
        }

        void Fragment::spreadGraph(std::shared_ptr<FragmentsGraph>& graph)
        {
            if (this->graph == graph)
                return;

            this->graph = graph;

            std::for_each(dependencies.begin(), dependencies.end(), [&graph](const std::shared_ptr<Fragment>& fragment)
                {
                    fragment->spreadGraph(graph);
                });
        }

        void Fragment::performUpdate(const Frame& frame)
        {

        }

        Fragment::Fragment():
            graph(new MegaFragmentsGraph(this)),
            lastUpdatedFor(0),
            id(nextId++)
        {

        }

        bool Fragment::isOrigin() const noexcept
        {
            return ((MegaFragmentsGraph*) graph.get())->isOrigin(this);
        }

        void Fragment::addDependency(std::shared_ptr<Fragment> dependency)
        {
            if (!dependency->isOrigin() && dependency->graph != this->graph)
                exception::throwNew("an attempt to add a non-origin fragment as a dependency was made");

            ((MegaFragmentsGraph*) graph.get())->merge(dependency->graph.get());
            dependency->spreadGraph(graph);
            dependencies.insert(dependency);
        }

        FragmentsGraph& Fragment::getGraph() const noexcept
        {
            return *graph;
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
