
#ifndef EGE_FLOW_EVENTUPDATEFRAGMENT_HXX
#define EGE_FLOW_EVENTUPDATEFRAGMENT_HXX

#include <ege/flow/fragment.hxx>
#include <private/ege/engine/control-thread.hxx>

namespace ege
{
    namespace flow
    {
        /**
         * \brief Update the events.
         * */
        class EventUpdateFragment: public Fragment
        {
            private:
                /**
                 * \brief Stores reference to the control thread.
                 * */
                engine::ControlThread& controlThread;

            protected:
                /**
                 * \brief Update events.
                 * \param frame The frame that is updating.
                 * */
                virtual void performUpdate(const Frame& frame);

            public:
                /**
                 * \brief Create an event update fragment, that fetch current scene from specified control thread.
                 * \param controlThread The specified control thread.
                 * */
                EventUpdateFragment(engine::ControlThread& controlThread);

                virtual ~EventUpdateFragment() {}
        };
    }
}

#endif
