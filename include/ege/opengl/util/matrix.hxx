
#ifndef EGE_OPENGL_UTIL_MATRIX_HXX
#define EGE_OPENGL_UTIL_MATRIX_HXX

#include <ege/math/matrix.hxx>

namespace ege
{
    namespace opengl
    {
        namespace util
        {
            /**
             * \brief Create a general scaling matrix.
             * \param x, y, z Specify scale factors along the x, y, and z axes, respectively.
             * \return The general scaling matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> scale(T x, T y, T z) noexcept;

            /**
             * \brief Create a general scaling matrix.
             * \param vector The vector containing scale factors along the x, y, and z axes, respectively.
             * \return The general scaling matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> scale(const math::Vector<3, T>& vector) noexcept;

            /**
             * \brief Create a translation matrix.
             * \param x, y, z The x, y, and z coordinates of a translation vector.
             * \return The translation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> translate(T x, T y, T z) noexcept;

            /**
             * \brief Create a translation matrix.
             * \param x, y, z The translation vector.
             * \return The translation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> translate(const math::Vector<3, T>& vector) noexcept;

            /**
             * \brief Create a rotation matrix, that rotates on X axis.
             * \param radians Specifies the angle of rotation.
             * \return The rotation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> rotateX(T radians) noexcept;

            /**
             * \brief Create a rotation matrix, that rotates on T axis.
             * \param radians Specifies the angle of rotation.
             * \return The rotation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> rotateY(T radians) noexcept;

            /**
             * \brief Create a rotation matrix, that rotates on Z axis.
             * \param radians Specifies the angle of rotation.
             * \return The rotation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> rotateZ(T radians) noexcept;

            /**
             * \brief Create a rotation matrix, that rotates on a vector.
             * \param radians Specifies the angle of rotation.
             * \param vx, vy, vz Specify the x, y, and z coordinates of the vector, respectively.
             * \param normalize If \c true, the vector will be normalized, if \c false not. Default is true.
             * \return The rotation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> rotate(T radians, T vx, T vy, T vz, bool normalize = true) noexcept;

            /**
             * \brief Create a rotation matrix, that rotates on a vector.
             * \param radians Specifies the angle of rotation.
             * \param vx, vy, vz The vector.
             * \param normalize If \c true, the vector will be normalized, if \c false not. Default is true.
             * \return The rotation matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> rotate(T radians, const math::Vector<3, T>& vector, bool normalize = true) noexcept;

            /**
             * \brief Create a perspective matrix.
             * \param left, right Specify the coordinates for the left and right vertical clipping planes.
             * \param bottom, top Specify the coordinates for the bottom and top horizontal clipping planes.
             * \param near, far Specify the distances to the near and far depth clipping planes.
             *     Both distances must be positive.
             * \return The perspective matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> frustum(T left, T right, T bottom, T top, T near, T far) noexcept;

            /**
             * \brief Create a projection matrix.
             * \param fovy Specifies the field of view angle, in degrees, in the y direction.
             * \param aspect Specifies the aspect ratio that determines the field of view in the x direction.
             *     The aspect ratio is the ratio of x (width) to y (height).
             * \param near Specifies the distance from the viewer to the near clipping plane (always positive).
             * \param far Specifies the distance from the viewer to the far clipping plane (always positive).
             * \return The projection matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> perspective(T fovy, T aspect, T near, T far) noexcept;

            /**
             * \brief Create a orthographic matrix.
             * \param left, right Specify the coordinates for the left and right vertical clipping planes.
             * \param bottom, top Specify the coordinates for the bottom and top horizontal clipping planes.
             * \param near, far Specify the distances to the nearer and farther depth clipping planes.
             *     These values are negative if the plane is to be behind the viewer.
             * \return The orthographic matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far) noexcept;

            /**
             * \brief Create a orthographic matrix.
             * \param left, right Specify the coordinates for the left and right vertical clipping planes.
             * \param bottom, top Specify the coordinates for the bottom and top horizontal clipping planes.
             * \return The orthographic matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> ortho2D(T left, T right, T bottom, T top) noexcept;

            /**
             * \brief Create viewing matrix derived from a reference point indicating the center
             *     of the scene and an UP vector.
             * \param centerX, centerY, centerZ Specifies the position of the reference point.
             * \param upX, upY, upZ Specifies the direction of the up vector.
             * \return The viewing matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> fromOriginLookAt(T centerX, T centerY, T centerZ, T upX, T upY, T upZ) noexcept;

            /**
             * \brief Create viewing matrix derived from a reference point indicating the center
             *     of the scene and an UP vector.
             * \param center Specifies the position of the reference point.
             * \param up Specifies the direction of the up vector.
             * \return The viewing matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> fromOriginLookAt(const math::Vector<3, T>& center, const math::Vector<3, T>& up) noexcept;

            /**
             * \brief Create viewing matrix derived from an eye point, a reference point indicating the center
             *     of the scene, and an UP vector.
             * \param eyeX, eyeY, eyeZ Specifies the position of the eye point.
             * \param centerX, centerY, centerZ Specifies the position of the reference point.
             * \param upX, upY, upZ Specifies the direction of the up vector.
             * \return The viewing matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ) noexcept;

            /**
             * \brief Create viewing matrix derived from an eye point, a reference point indicating the center
             *     of the scene, and an UP vector.
             * \param eye Specifies the position of the eye point.
             * \param center Specifies the position of the reference point.
             * \param up Specifies the direction of the up vector.
             * \return The viewing matrix.
             * */
            template<typename T = float>
            math::Matrix<4, 4, T> lookAt(const math::Vector<3, T>& eye, const math::Vector<3, T>& center, const math::Vector<3, T>& up) noexcept;
        }
    }
}

#include "matrix.txx"

#endif
