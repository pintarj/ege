
#ifndef EGE_OPENGL_RASTERIZATION_HXX
#define EGE_OPENGL_RASTERIZATION_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enable smooth line drawing.
         *
         * If enabled, draw lines with correct filtering. Otherwise, draw aliased lines.
         * */
        void enableLineSmooth() noexcept;

        /**
         * \brief Disable smooth line drawing.
         * \sa enableLineSmooth()
         * */
        void disableLineSmooth() noexcept;

        /**
         * \brief Enable smooth polygon drawing.
         *
         * If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons.
         * */
        void enablePolygonSmooth() noexcept;

        /**
         * \brief Disable smooth polygon drawing.
         * \sa enablePolygonSmooth()
         * */
        void disablePolygonSmooth() noexcept;
    }
}

#endif
