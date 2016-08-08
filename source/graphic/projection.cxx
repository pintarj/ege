#include <ege/graphic/projection.hxx>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace ege::graphic;


Projection::Projection( const float* matrix )
{
        memcpy( this->matrix, matrix, 16 * sizeof( float ) );
}


const float* Projection::getMatrix()
{
        return matrix;
}
