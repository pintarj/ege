#include <ege/graphic/projection.hxx>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace ege::graphic;


Projection::Projection( const float* matrix )
{
        memcpy( this->matrix, matrix, 16 * sizeof( float ) );
}


const float* Projection::getMatrix()
{
        return matrix;
}


OrthoProjection::OrthoProjection( float left, float right, float bottom, float top, float near, float far ):
        Projection( glm::value_ptr( glm::ortho( left, right, bottom, top, near, far ) ) )
{

}


OrthoProjection::OrthoProjection( float left, float right, float bottom, float top ):
        OrthoProjection( left, right, bottom, top, -1.0f, +1.0f )
{

}
