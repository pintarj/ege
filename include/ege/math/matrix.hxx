
#ifndef EGE_MATH_MATRIX_HXX
#define EGE_MATH_MATRIX_HXX

#include <ege/math/vector.hxx>

namespace ege
{
    namespace math
    {
        /**
         * \brief Represent a mathematical matrix.
         * \param M The vertical dimension of matrix.
         * \param N The horizontal dimension of matrix.
         * \param T The type of the vector's components.
         * */
        template<unsigned M, unsigned N = M, typename T = float>
        class Matrix
        {
            private:
                /**
                 * \brief Here are stored components of the matrix.
                 * */
                T components[M][N];

            public:
                /**
                 * \brief Creates a matrix initializing all components with a specific value.
                 * \param value The specific value. Default is 0.
                 * */
                Matrix(T value = 0) noexcept;

                /**
                 * \brief Creates a matrix initializing components from an array.
                 * \param array The array from which values will be copied.
                 * */
                Matrix(T (& array)[M][N]) noexcept;

                /**
                 * \brief Access the matrix's row at a specific index.
                 * \param index The index of the row.
                 * */
                T* operator [](unsigned index) noexcept;

                /**
                 * \brief Access the matrix's row at a specific index.
                 * \param index The index of the row.
                 * */
                const T* operator [](unsigned index) const noexcept;
        };

        /**
         * \brief Multiply two matrices.
         * \param left The left matrix of the operation.
         * \param right The right matrix of the operation.
         * \return The result matrix of the operation.
         * */
        template<unsigned M, unsigned N, unsigned P, typename T>
        Matrix<M, P, T> operator *(Matrix<M, N, T> const& left, Matrix<N, P, T> const& right) noexcept;

        /**
         * \brief Multiply two matrices and stores result in the first one.
         * \param left The left matrix of the operation.
         * \param right The right matrix of the operation.
         * \return The left matrix with the result stored in it.
         * */
        template<unsigned M, unsigned N, unsigned P, typename T>
        Matrix<M, P, T>& operator *=(Matrix<M, N, T>& left, Matrix<N, P, T> const& right) noexcept;

        /**
         * \brief Create an identity matrix.
         * */
        template<unsigned M, typename T = float>
        Matrix<M, M, T> identity() noexcept;
    }
}

#include "matrix.txx"

#endif
