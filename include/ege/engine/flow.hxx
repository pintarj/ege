
#ifndef EGE_ENGINE_FLOW_HXX
#define EGE_ENGINE_FLOW_HXX

#include <ege/engine/configuration.hxx>

namespace ege
{
    namespace engine
    {
        /**
         * \brief Starts an engine using a specific configuration.
         * \param configuration The engine configuration.
         * */
        void start(Configuration& configuration);

        /**
         * \brief Requires the engine stop.
         * */
        void requireStop() noexcept;

        /**
         * \brief Requires the engine restart.
         * */
        void requireRestart() noexcept;
    }
}

#endif
