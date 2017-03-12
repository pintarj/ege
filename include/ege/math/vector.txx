#include <ege/math/vector.hxx>
#include <cmath>
#include <cstddef>
#include <cstring>

namespace ege
{
    namespace math
    {
        template<unsigned N, typename T>
        Vector<N, T>::Vector(T value) noexcept
        {
            for (unsigned i = 0; i < N; ++i)
                components[i] = value;
        }
        
        template<unsigned N, typename T>
        Vector<N, T>::Vector(T (& components)[N]) noexcept
        {
            for (unsigned i = 0; i < N; ++i)
                this->components[i] = components[i];
        }

        template<unsigned N, typename T>
        Vector<N, T>::Vector(std::initializer_list<T> list) noexcept
        {
            auto iterator = list.begin();
            unsigned n = n = std::min((std::size_t) N, list.size());

            for (unsigned i = 0; i < n; ++i)
                this->components[i] = *iterator++;

            for (unsigned i = n; i < N; ++i)
                this->components[i] = 0;
        }

        template<unsigned N, typename T>
        T Vector<N, T>::length() const noexcept
        {
            return std::sqrt(dotProduct(*this, *this));
        }

        template<unsigned N, typename T>
        Vector<N, T> Vector<N, T>::normalized() const noexcept
        {
            return *this / length();
        }

        template<unsigned N, typename T>
        T& Vector<N, T>::operator [](unsigned index) noexcept
        {
            return components[index];
        }

        template<unsigned N, typename T>
        const T& Vector<N, T>::operator [](unsigned index) const noexcept
        {
            return components[index];
        }

        template<unsigned N, typename T = float>
        Vector<N, T> operator +(const Vector<N, T>& left, const Vector<N, T>& right) noexcept
        {
            T components[N];

            for (unsigned i = 0; i < N; ++i)
                components[i] = left[i] + right[i];

            return Vector<N, T>(components);
        }

        template<unsigned N, typename T = float>
        Vector<N, T> operator -(const Vector<N, T>& vector) noexcept
        {
            T components[N];

            for (unsigned i = 0; i < N; ++i)
                components[i] = -vector[i];

            return Vector<N, T>(components);
        }

        template<unsigned N, typename T = float>
        Vector<N, T> operator -(const Vector<N, T>& left, const Vector<N, T>& right) noexcept
        {
            return left + (-right);
        }

        template<unsigned N, typename T = float>
        Vector<N, T> operator *(T scalar, Vector<N, T> const& vector) noexcept
        {
            T components[N];

            for (unsigned i = 0; i < N; ++i)
                components[i] = scalar * vector[i];

            return Vector<N, T>(components);
        }

        template<unsigned N, typename T = float>
        Vector<N, T> operator *(Vector<N, T> const& vector, T scalar) noexcept
        {
            return scalar * vector;
        }

        template<unsigned N, typename T = float>
        Vector<N, T> operator /(Vector<N, T> const& vector, T scalar) noexcept
        {
            return (1 / scalar) * vector;
        }

        template<unsigned N, typename T = float>
        T dotProduct(const Vector<N, T>& left, const Vector<N, T>& right) noexcept
        {
            T sum = 0;

            for (unsigned i = 0; i < N; ++i)
                sum += left[i] * right[i];

            return sum;
        }

        template<typename T = float>
        Vector<3, T> crossProduct(const Vector<3, T>& left, const Vector<3, T>& right) noexcept
        {
            T components[3];
            components[0] = left[1] * right[2] - left[2] * right[1];
            components[1] = left[2] * right[0] - left[0] * right[2];
            components[2] = left[0] * right[1] - left[1] * right[0];
            return Vector<3, T>(components);
        }
    }
}
