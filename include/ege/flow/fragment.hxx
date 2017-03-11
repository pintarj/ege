
#ifndef EGE_FLOW_FRAGMENT_HXX
#define EGE_FLOW_FRAGMENT_HXX

#include <memory>
#include <set>
#include <ege/flow/executable.hxx>
#include <ege/flow/fragment.hxx>
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
                 * \brief The dependencies of \c this fragment.
                 * */
                std::set<std::shared_ptr<Fragment>> dependencies;

                /**
                 * \brief Stores the Fragment object that are dependent by \c this object.
                 * */
                std::set<Fragment*> dependencyOf;

                /**
                 * \brief Stores the id of the last frame at which \c this was updated.
                 * */
                Frame::Id lastUpdatedFor;

                /**
                 * \brief Stores the number of outdated dependencies.
                 *
                 * When this counter reach zero: it can be executed.
                 * */
                unsigned outDatedDependenciesCounter;

                /**
                 * \brief Decreases outDatedDependenciesCounter and eventually executes executable.
                 * \param frame The frame that is updating.
                 * */
                void onDependencyUpdate(const Frame& frame);

                /**
                 * \brief Call onDependencyUpdate() method of objects stored in dependencyOf.
                 * \param frame The frame that is updating.
                 * */
                void decreaseDependencyOfCounters(const Frame& frame);

                /**
                 * \brief Require execution of performUpdate() followed by decreaseDependencyOfCounters()
                 *     on an ThreadExecutor.
                 * \param frame The frame that is updating.
                 *
                 * Depending on the result of requiresUpdateExecutionOnGraphicThread() the two functions
                 * will be executed on graphic thread or on the ParallelNucleus in engine resources.
                 * */
                void requireExecution(const Frame& frame);

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
                 * \brief Add a dependency fragment to \c this.
                 * \param dependency The dependency fragment.
                 * \sa removeDependency()
                 *
                 * The dependency fragments are updated before \c this fragment while
                 * updating fragments graph.
                 * */
                void addDependency(std::shared_ptr<Fragment> dependency);

                /**
                 * \brief Remove a dependency fragment from \c this.
                 * \param dependency The dependency fragment.
                 * \sa addDependency()
                 * */
                void removeDependency(std::shared_ptr<Fragment> dependency);

                /**
                 * \brief Tells if \c this is updated.
                 * \return \c True if it's updated, \c false otherwise.
                 * \sa update()
                 *
                 * Default implementation returns \c false. \n
                 * Note on graphic content: this method is executing on control thread: this mean, that execution
                 * of graphic function is not available. \n
                 * Note on performance: this method is used to NOT update what'is already updated. It'll be used
                 * by control thread to determinate what to execute on frame update, so implementation should be
                 * possibly short.
                 * */
                virtual bool isUpdated();

                /**
                 * \brief Update \c this fragment.
                 * \param frame The frame that is updating.
                 * \sa performUpdate()
                 * \sa requiresUpdateExecutionOnGraphicThread()
                 *
                 * The implementation will firstly check if \c this was already updated for the last frame, then if it
                 * was not: method will check if need to be updated via isUpdated() method. If it's not: all
                 * dependencies will be recursively updated and the performUpdate() method invoked. \n
                 * Parallel execution optimization: implementation would not simply call recursively dependencies's
                 * update() method: there is a system, that allows parallel execution of fragment update starting from
                 * leafs and moving downward to fragment's origin (this is done by control thread). :) \n
                 * Do not call this method: it's meant for engine purposes.
                 * */
                virtual void update(const Frame& frame);

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

                /**
                 * \brief Tells if \c this Fragment is a leaf (has no dependencies).
                 * \return \c True if it's a leaf, \c false otherwise.
                 * */
                bool isLeaf() const;
        };
    }
}

#endif
