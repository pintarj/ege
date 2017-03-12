#include <ege/math/triangle.hxx>

namespace ege
{
    namespace math
    {
        template<typename T>
        Triangle<T>::Triangle(Vector<3, T> const& v0, Vector<3, T> const& v1, Vector<3, T> const& v2) noexcept:
            vertices({v0, v1, v2})
        {

        }

        template<typename T>
        Vector<3, T>& Triangle<T>::operator [](unsigned index) noexcept
        {
            return vertices[index];
        }

        template<typename T>
        Vector<3, T> const& Triangle<T>::operator [](unsigned index) const noexcept
        {
            return vertices[index];
        }

        template<typename T>
        Vector<3, T> Triangle<T>::normal(bool clockWise) const noexcept
        {
            if (clockWise)
                return crossProduct(vertices[2] - vertices[0], vertices[1] - vertices[0]).normalized();
            else
                return crossProduct(vertices[1] - vertices[0], vertices[2] - vertices[0]).normalized();
        }
    }
}
