
#ifndef EGE_MATH_MATRIX_HXX
#define EGE_MATH_MATRIX_HXX

#include <ege/math/vector.hxx>

namespace ege
{
    namespace math
    {
        template<unsigned M, unsigned N = M, typename T = float>
        class Matrix
        {
            private:
                T raw[M][N];

            public:
                Matrix();

                Matrix(T (& raw)[M][N]);

                T* operator [](unsigned index);

                const T* operator [](unsigned index) const;
        };

        template<unsigned M, unsigned N, unsigned P, typename T = float>
        Matrix<M, P, T> operator *(Matrix<M, N, T> const& left, Matrix<N, P, T> const& right);

        template<unsigned M, unsigned N, unsigned P, typename T = float>
        Matrix<M, P, T>& operator *=(Matrix<M, N, T>& left, Matrix<N, P, T> const& right);

        namespace matrix
        {
            template<unsigned M = 4, typename T = float>
            Matrix<M, M, T> identity();

            template<typename T = float>
            Matrix<4, 4, T> scale(T x, T y, T z);

            template<typename T = float>
            Matrix<4, 4, T> scale(Vector<3, T> const& vector);

            template<typename T = float>
            Matrix<4, 4, T> translate(T x, T y, T z);

            template<typename T = float>
            Matrix<4, 4, T> translate(Vector<3, T> const& vector);

            template<typename T = float>
            Matrix<4, 4, T> rotateX(T radians);

            template<typename T = float>
            Matrix<4, 4, T> rotateY(T radians);

            template<typename T = float>
            Matrix<4, 4, T> rotateZ(T radians);

            template<typename T = float>
            Matrix<4, 4, T> rotate(T radians, T vx, T vy, T vz, bool normalize = true);

            template<typename T = float>
            Matrix<4, 4, T> rotate(T radians, Vector<3, T> const& vector, bool normalize = true);

            template<typename T = float>
            Matrix<4, 4, T> frustum(T left, T right, T bottom, T top, T near, T far);

            template<typename T = float>
            Matrix<4, 4, T> perspective(T radians, T ratio, T near, T far);

            template<typename T = float>
            Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far);

            template<typename T = float>
            Matrix<4, 4, T> ortho2D(T left, T right, T bottom, T top);

            template<typename T = float>
            Matrix<4, 4, T> fromOriginLookAt(T centerX, T centerY, T centerZ, T upX, T upY, T upZ);

            template<typename T = float>
            Matrix<4, 4, T> fromOriginLookAt(Vector<3, T> const& center, Vector<3, T> const& up);

            template<typename T = float>
            Matrix<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ);

            template<typename T = float>
            Matrix<4, 4, T> lookAt(Vector<3, T> const& eye, Vector<3, T> const& center, Vector<3, T> const& up);
        }
    }
}

#include "matrix.txx"

#endif
