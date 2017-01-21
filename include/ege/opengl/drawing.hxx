
#ifndef EGE_OPENGL_DRAWING_HXX
#define EGE_OPENGL_DRAWING_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumeration of draw modes.
         * */
        enum class DrawMode: unsigned int
        {
            POINTS                      = 0x0,
            PATCHES                     = 0xE,
            LINES                       = 0x1,
            LINE_LOOP                   = 0x2,
            LINE_STRIP                  = 0x3,
            LINES_ADJACENCY             = 0xA,
            LINE_STRIP_ADJACENCY        = 0xB,
            TRIANGLES                   = 0x4,
            TRIANGLE_STRIP              = 0x5,
            TRIANGLE_FAN                = 0x6,
            TRIANGLES_ADJACENCY         = 0xC,
            TRIANGLE_STRIP_ADJACENCY    = 0xD
        };

        /**
         * \brief Render the primitives from array data.
         * \param mode Specifies what kind of primitives to render.
         * \param first Specifies the starting index in the enabled arrays.
         * \param count Specifies the number of indices to be rendered.
         * */
        void drawArrays(DrawMode mode, int first, int count);

        /**
         * \brief Draw multiple instances of a range of elements.
         * \param mode Specifies what kind of primitives to render.
         * \param first Specifies the starting index in the enabled arrays.
         * \param count Specifies the number of indices to be rendered.
         * \param instanceCount Specifies the number of instances of the specified range of indices to be rendered.
         * */
        void drawArraysInstanced(DrawMode mode, int first, int count, int instanceCount);

        /**
         * \brief Draw multiple instances of a range of elements with offset applied to instanced attributes.
         * \param mode Specifies what kind of primitives to render.
         * \param first Specifies the starting index in the enabled arrays.
         * \param count Specifies the number of indices to be rendered.
         * \param instanceCount Specifies the number of instances of the specified range of indices to be rendered.
         * \param baseInstance Specifies the base instance for use in fetching instanced vertex attributes.
         * */
        void drawArraysInstancedBaseInstance(DrawMode mode, int first, int count, int instanceCount, unsigned int baseInstance);

        /**
         * \brief Render multiple sets of primitives from array data.
         * \param mode Specifies what kind of primitives to render.
         * \param first Points to an array of starting indices in the enabled arrays.
         * \param count Points to an array of the number of indices to be rendered.
         * \param drawCount Specifies the size of the first and count arrays.
         * */
        void multiDrawArrays(DrawMode mode, int* first, int* count, int drawCount);
    }
}

#endif
