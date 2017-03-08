
#ifndef PRIVATE_EGE_ENGINE_INIFINI_HXX
#define PRIVATE_EGE_ENGINE_INIFINI_HXX

namespace ege
{
    namespace engine
    {
        /**
         * \brief Used to initialize and/or terminating modules.
         * */
        class IniFini
        {
            public:
                /**
                 * \brief Register this object to "iniFini"s list.
                 * */
                IniFini();

                /**
                 * \brief Unregister this object from "iniFini"s list.
                 * */
                virtual ~IniFini();

                /**
                 * \brief Called before real engine initialization.
                 * \sa ege::engine::iniFini::initialize()
                 *
                 * Default implementation is an empty function.
                 * */
                virtual void initialize();

                /**
                 * \brief Called after real engine termination.
                 * \sa ege::engine::iniFini::terminate()
                 *
                 * Default implementation is an empty function.
                 * */
                virtual void terminate();
        };

        namespace iniFini
        {
            /**
             * \brief Call IniFini::initialize() of all registered "iniFini"s.
             * \sa ege::engine::start()
             *
             * Function invoked by engine before the real initialization.
             * */
            void initialize();

            /**
             * \brief Call IniFini::terminate() of all registered "iniFini"s.
             * \sa ege::engine::start()
             *
             * Function invoked by engine after the real termination.
             * */
            void terminate();
        }
    }
}

#endif
