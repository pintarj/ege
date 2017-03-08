
#ifndef EGE_FLOW_FRAGMENT_HXX
#define EGE_FLOW_FRAGMENT_HXX

namespace ege
{
    namespace flow
    {
        class Fragment;
    }
}

#include <memory>
#include <set>
#include <ege/flow/fragments-graph.hxx>
#include <ege/flow/frame.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Represent a scene's fragment.
         * */
        class Fragment
        {
            private:
                /**
                 * \brief The graph that contains \c this fragment.
                 * */
                std::shared_ptr<FragmentsGraph> graph;

                /**
                 * \brief The dependencies of \c this fragment.
                 * */
                std::set<std::shared_ptr<Fragment>> dependencies;

                /**
                 * \brief Stores the id of the last frame at which \c this was updated.
                 * */
                Frame::Id lastUpdatedFor;

                /**
                 * \brief Recursively sets the graph to \c this fragment and his dependencies.
                 * \param graph The graph to spread.
                 * */
                void spreadGraph(std::shared_ptr<FragmentsGraph>& graph);

            public:
                /**
                 * \brief The fragment's id type.
                 * */
                typedef unsigned long long Id;

                /**
                 * \brief The id of the fragment.
                 *
                 * It's automatically generated in constructor.
                 * */
                const Id id;

                /**
                 * \brief Creates a fragment.
                 *
                 * It also creates an independent graph, that has \c this fragment as the origin.
                 * */
                Fragment();

                virtual ~Fragment() {}

                /**
                 * \brief Tells if \c this fragment is the graph's origin.
                 * \return \c True if it's the origin, \c false otherwise.
                 * */
                bool isOrigin() const noexcept;

                /**
                 * \brief Add a dependency fragment to \c this.
                 * \param dependency The dependency fragment.
                 *
                 * The dependency fragments are updated before \c this fragment while
                 * updating fragments graph.
                 * */
                void addDependency(std::shared_ptr<Fragment> dependency);

                /**
                 * \brief Returns the graph that contains \c this fragment.
                 * \return The graph reference.
                 * Note that, the reference is valid only until \c this object exists. \n
                 * */
                FragmentsGraph& getGraph() const noexcept;
        };
    }
}

#endif
