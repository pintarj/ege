
#ifndef EGE_MATH_VECTOR_HXX
#define EGE_MATH_VECTOR_HXX

#include <initializer_list>

namespace ege
{
    namespace math
    {
        /**
         * \brief Represent a mathematical vector.
         * \param N The dimension of vector.
         * \param T The type of the vector's components.
         * */
        template<unsigned N = 3, typename T = float>
        class Vector
        {
            private:
                /**
                 * \brief Here are stored components of the vector.
                 * */
                T components[N];

            public:
                /**
                 * \brief Creates a vector initializing all components with a specific value.
                 * \param value The specific value. Default is 0.
                 * */
                Vector(T value = 0) noexcept;

                /**
                 * \brief Creates a vector initializing components from an array.
                 * \param array The array from which values will be copied.
                 * */
                Vector(T (& array)[N]) noexcept;

                /**
                 * \brief Creates a vector initializing components from a std::initializer_list.
                 * \param list The list from which values will be copied.
                 *
                 * If list is shorter than vector dimension: remaining components will be set to zero.
                 * */
                Vector(std::initializer_list<T> list) noexcept;

                /**
                 * \brief Returns the length of the vector.
                 * \return The length of the vector.
                 * */
                T length() const noexcept;

                /**
                 * \brief Returns the normalized vector.
                 * \return The normalized vector.
                 * */
                Vector<N, T> normalized() const noexcept;
                
                /**
                 * \brief Access the vector's component at a specific index.
                 * \param index The index of the component.
                 * */
                T& operator [](unsigned index) noexcept;

                /**
                 * \brief Access the vector's component at a specific index.
                 * \param index The index of the component.
                 * */
                const T& operator [](unsigned index) const noexcept;
        };

        /**
         * \brief Add two vectors.
         * \param left The left vector of the operation.
         * \param right The right vector of the operation.
         * \return The result of the operation.
         * */
        template<unsigned N, typename T>
        Vector<N, T> operator +(const Vector<N, T>& left, const Vector<N, T>& right) noexcept;

        /**
         * \brief Negate vector components.
         * \param The vector to negate.
         * \return The result of the operation.
         * */
        template<unsigned N, typename T>
        Vector<N, T> operator -(const Vector<N, T>& vector) noexcept;

        /**
         * \brief Subtract one vector from vectors.
         * \param left The left vector of the operation (vector from which subtract).
         * \param right The right vector of the operation (vector to subtract).
         * \return The result of the operation.
         * */
        template<unsigned N, typename T>
        Vector<N, T> operator -(const Vector<N, T>& left, const Vector<N, T>& right) noexcept;

        /**
         * \brief Multiply a vector with a scalar.
         * \param scalar The scalar.
         * \param vector The vector.
         * \return The result of the operation.
         *
         * The scalar is on left. The vector is on right.
         * */
        template<unsigned N, typename T>
        Vector<N, T> operator *(T scalar, const Vector<N, T>& vector) noexcept;

        /**
         * \brief Multiply a vector with a scalar.
         * \param scalar The scalar.
         * \param vector The vector.
         * \return The result of the operation.
         *
         * The scalar is on right. The vector is on left.
         * */
        template<unsigned N, typename T>
        Vector<N, T> operator *(const Vector<N, T>& vector, T scalar) noexcept;

        /**
         * \brief Divide a vector with a scalar.
         * \param scalar The scalar.
         * \param vector The vector.
         * \return The result of the operation.
         * */
        template<unsigned N, typename T>
        Vector<N, T> operator /(const Vector<N, T>& vector, T scalar) noexcept;

        /**
         * \brief Performs a dot product.
         * \param left The left vector of the operation.
         * \param right The right vector of the operation.
         * \return The operation result.
         * */
        template<unsigned N, typename T>
        T dotProduct(const Vector<N, T>& left, const Vector<N, T>& right) noexcept;

        /**
         * \brief Performs a cross product.
         * \param left The left vector (of dimension 3) of the operation.
         * \param right The right vector (of dimension 3) of the operation.
         * \return The operation result.
         * */
        template<typename T>
        Vector<3, T> crossProduct(const Vector<3, T>& left, const Vector<3, T>& right) noexcept;
    }
}

#include "vector.txx"

#endif
