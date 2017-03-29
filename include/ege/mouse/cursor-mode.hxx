
#ifndef EGE_MOUSE_CURSORMODE_HXX
#define EGE_MOUSE_CURSORMODE_HXX

namespace ege
{
    namespace mouse
    {
        /**
         * \brief Enumerate the cursor modes.
         *
         * NORMAL: The regular arrow cursor is used. \n
         * DISABLED: Will hide the cursor and lock it to the specified window. \n
         * HIDDEN: Become hidden when it is over the window.
         * */
        enum class CursorMode: unsigned
        {
            NORMAL      = 0x00034001,
            HIDDEN      = 0x00034002,
            DISABLED    = 0x00034003
        };
    }
}

#endif
