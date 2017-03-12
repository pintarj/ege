#include <ege/math/matrix.hxx>
#include <cmath>

namespace ege
{
    namespace math
    {
        template<unsigned M, unsigned N, typename T>
        Matrix<M, N, T>::Matrix(T value) noexcept
        {
            for (unsigned i = 0; i < M; ++i)
                for (unsigned j = 0; j < N; ++j)
                    this->components[i][j] = value;
        }

        template<unsigned M, unsigned N, typename T>
        Matrix<M, N, T>::Matrix(T (& components)[M][N]) noexcept
        {
            for (unsigned i = 0; i < M; ++i)
                for (unsigned j = 0; j < N; ++j)
                    this->components[i][j] = components[i][j];
        }

        template<unsigned M, unsigned N, typename T>
        T* Matrix<M, N, T>::operator [](unsigned index) noexcept
        {
            return components[index];
        }

        template<unsigned M, unsigned N, typename T>
        const T* Matrix<M, N, T>::operator [](unsigned index) const noexcept
        {
            return components[index];
        }

        template<unsigned M, unsigned N, unsigned P, typename T>
        Matrix<M, P, T> operator *(Matrix<M, N, T> const& left, Matrix<N, P, T> const& right) noexcept
        {
            T components[M][P];

            for (unsigned i = 0; i < M; ++i)
            {
                for (unsigned j = 0; j < P; ++j)
                {
                    T sum = 0;

                    for (unsigned k = 0; k < N; ++k)
                        sum += left[i][k] * right[k][j];

                    components[i][j] = sum;
                }
            }

            return Matrix<M, P, T>(components);
        }

        template<unsigned M, unsigned N, unsigned P, typename T>
        Matrix<M, P, T>& operator *=(Matrix<M, N, T>& left, Matrix<N, P, T> const& right) noexcept
        {
            Matrix<M, P, T> tmp = left * right;
            left = tmp;
        }

        template<unsigned M, typename T>
        Matrix<M, M, T> identity() noexcept
        {
            T matrix[M][M];

            for (unsigned i = 0; i < M; ++i)
                for (unsigned j = 0; j < M; ++j)
                    matrix[i][j] = (i == j) ? 1 : 0;

            return Matrix<M, M, T>(matrix);
        }
    }
}
