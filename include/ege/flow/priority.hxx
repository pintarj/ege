
#ifndef EGE_FLOW_PRIORITY_HXX
#define EGE_FLOW_PRIORITY_HXX

namespace ege
{
    namespace flow
    {
        /**
         * \brief Enumerate execution priorities.
         *
         * Default is MEDIUM.
         * */
        enum class Priority: unsigned
        {
                EXTREME = 4,
                HIGH    = 3,
                MEDIUM  = 2,
                LOW     = 1,
                ZERO    = 0,
                DEFAULT = MEDIUM
        };
    }
}

#endif
