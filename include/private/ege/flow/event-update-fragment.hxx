
#ifndef EGE_FLOW_EVENTUPDATEFRAGMENT_HXX
#define EGE_FLOW_EVENTUPDATEFRAGMENT_HXX

#include <ege/flow/fragment.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Update the events.
         * */
        class EventUpdateFragment: public Fragment
        {
            protected:
                /**
                 * \brief Update events.
                 * \param frame The frame that is updating.
                 * */
                virtual void performUpdate(const Frame& frame);

            public:
                /**
                 * \brief Create an event update fragment.
                 * */
                EventUpdateFragment();

                virtual ~EventUpdateFragment() {}
        };
    }
}

#endif
