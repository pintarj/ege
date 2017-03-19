
#ifndef PRIVATE_EGE_FLOW_THREAD_HXX
#define PRIVATE_EGE_FLOW_THREAD_HXX

#include <string>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Change the name of this thread.
         * \param name The new name of the thread.
         * \return \c True if the name was successfully changed, \c false otherwise.
         * */
        bool changeThisThreadName(const std::string& name);
    }
}

#endif
