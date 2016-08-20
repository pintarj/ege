#include <ege/graphic/geometry/projection.hxx>
#include <ege_private/graphic/geometry/matrix.hxx>


using namespace ege::graphic::geometry;
using namespace ege_private::graphic::geometry;


const float* Projection::getMatrix()
{
        return matrix;
}


OrthoProjection::OrthoProjection( float left, float right, float bottom, float top, float near, float far )
{
        matrix::ortho( matrix, left, right, bottom, top, near, far );
}


OrthoProjection::OrthoProjection( float left, float right, float bottom, float top )
{
        matrix::ortho2D( matrix, left, right, bottom, top );
}
