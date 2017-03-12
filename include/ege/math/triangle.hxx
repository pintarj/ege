
#ifndef EGE_MATH_TRIANGLE_HXX
#define EGE_MATH_TRIANGLE_HXX

#include <ege/math/vector.hxx>

namespace ege
{
    namespace math
    {
        /**
         * \brief A mathematical triangle (represented by 3 vectors).
         * \param T The type of the vector's components.
         * */
        template<typename T = float>
        class Triangle
        {
            private:
                /**
                 * \brief The vectors representing the triangle.
                 * */
                Vector<3, T> vertices[3];

            public:
                /**
                 * \brief Creates a triangle.
                 * \param v0, v1, v2 The vectors that define the triangle.
                 * */
                Triangle(const Vector<3, T>& v0, const Vector<3, T>& v1, const Vector<3, T>& v2) noexcept;

                /**
                 * \brief Access a vector of the triangle at the specific index.
                 * \param index The index.
                 * */
                Vector<3, T>& operator [](unsigned index) noexcept;

                /**
                 * \brief Access a vector of the triangle at the specific index.
                 * \param index The index.
                 * */
                const Vector<3, T>& operator [](unsigned index) const noexcept;

                /**
                 * \brief Calculates the normal of the triangle.
                 * \param clockWise If it's \c true the vectors are treated to be in clockwise order,
                 *     if \c false then are treated to be in counter-clockwise order. Default is \c false.
                 * */
                Vector<3, T> normal(bool clockWise = false) const noexcept;
        };
    }
}

#include "triangle.txx"

#endif
