#include <ege/graphic/geometry/transform.hxx>
#include <ege_private/graphic/geometry/matrix.hxx>


using namespace ege::graphic::geometry;
using namespace ege_private::graphic::geometry;


Transformation::Transformation()
{
        dirty = true;
}


const float* Transformation::getMatrix()
{
        if ( dirty )
        {
                calculate();
                dirty = false;
        }

        return ( const float* ) matrix;
}


void RotateTransformation::setAngle( float radians )
{
        this->radians = radians;
        dirty = true;
}


void RotateTransformation::setVector( float* vector )
{
        this->vector[ 0 ] = vector[ 0 ];
        this->vector[ 1 ] = vector[ 1 ];
        this->vector[ 2 ] = vector[ 2 ];
        dirty = true;
}


void RotateTransformation::setVector( float x, float y, float z )
{
        float vector[] = { x, y, z };
        setVector( vector );
}


void RotateTransformation::calculate()
{
        matrix::rotate( matrix, radians, vector[ 0 ], vector[ 1 ], vector[ 2 ] );
}