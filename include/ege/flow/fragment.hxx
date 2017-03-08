
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

            protected:
                /**
                 * \brief Update \c this fragment.
                 * \param frame The frame that is updating.
                 * \sa update()
                 * \sa requiresUpdateExecutionOnGraphicThread()
                 *
                 * This method will be automatically called by the update() method. \n
                 * Default implementation is an empty function.
                 * */
                virtual void performUpdate(const Frame& frame);

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

                /**
                 * \brief Tells if \c this is updated.
                 * \return \c True if it's updated, \c false otherwise.
                 * \sa update()
                 *
                 * Default implementation returns \c false.
                 * */
                virtual bool isUpdated();

                /**
                 * \brief Update \c this fragment.
                 * \param frame The frame that is updating.
                 * \sa update()
                 *
                 * The implementation will firstly check if \c this was already updated for the last frame, then if it
                 * was not: method will check if need to be updated via isUpdated() method.
                 * If it's not: all dependencies will be recursively updated and the performUpdate() method invoked. \n
                 * Implementation code:
                 * \code
                 * if (lastUpdatedFor == frame.id)
                 *     return;
                 *
                 * if (!isUpdated())
                 * {
                 *     for (auto& dependency : dependencies)
                 *         dependency->update(frame);
                 *
                 *     performUpdate(frame);
                 * }
                 *
                 * lastUpdatedFor = frame.id;
                 * \endcode
                 * */
                void update(const Frame& frame);

                /**
                 * \brief Tells to engine if the performUpdate() implementation requires execution on graphic thread.
                 * \return \c True if execution on graphic thread is required. Default implementation returns \c true.
                 *
                 * All the graphic commands have to be executed on graphic thread. For example: all the methods
                 * in the namespace ege::opengl have to be executed on graphic thread. \n
                 * If you don't know if your Updateable have to be executed on a graphic thread, then leave the
                 * implementation unmodified. \n
                 * Engine could massively optimize the execution of the application where there are some Updateable
                 * objects that doesn't require graphic thread, for example can execute those objects on different
                 * numbers of threads (using all the CPU's cores).
                 * */
                virtual bool requiresUpdateExecutionOnGraphicThread() const;
        };
    }
}

#endif
