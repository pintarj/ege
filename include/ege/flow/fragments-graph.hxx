
#ifndef EGE_FLOW_FRAGMENTSGRAPH_HXX
#define EGE_FLOW_FRAGMENTSGRAPH_HXX

namespace ege
{
    namespace flow
    {
        class FragmentsGraph;
    }
}

#include <ege/flow/fragment.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Collect data about a fragments graph.
         * \sa Fragment
         * */
        class FragmentsGraph
        {
            public:
                virtual ~FragmentsGraph() {}

                /**
                 * \brief Tells if the graph has changed.
                 * \return \c True if has changed, \c false otherwise.
                 *
                 * Graph is changed if new fragments was added, new dependencies created,
                 * some fragment was deleted, ... \n
                 * */
                virtual bool hasChanged() = 0;

                /**
                 * \brief Returns the number of fragments in the graph.
                 * \return The number of fragments in graph.
                 * */
                virtual unsigned getFragmentsCount() = 0;

                /**
                 * \brief Returns the number of dependencies in the graph.
                 * \return The number of dependencies in graph.
                 * */
                virtual unsigned getDependenciesCount() = 0;
        };
    }
}

#endif
