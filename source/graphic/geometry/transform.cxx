#include <ege/graphic/geometry/transform.hxx>
#include <ege_private/graphic/geometry/matrix.hxx>
#include <cstring>


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
                dirty = false;
                calculate();
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


void TranslateTransformation::setVector( float* vector )
{
        this->vector[ 0 ] = vector[ 0 ];
        this->vector[ 1 ] = vector[ 1 ];
        this->vector[ 2 ] = vector[ 2 ];
        dirty = true;
}


void TranslateTransformation::setVector( float x, float y, float z )
{
        float vector[] = { x, y, z };
        setVector( vector );
}


void TranslateTransformation::calculate()
{
        matrix::translate( matrix, vector[ 0 ], vector[ 1 ], vector[ 2 ] );
}


void TransformationPipeline::setTransformations( Transformation** transformations, size_t count )
{
        this->transformations = transformations;
        this->count = count;
        dirty = true;
}


void TransformationPipeline::calculate()
{
        std::memcpy( matrix, transformations[ 0 ]->getMatrix(), 16 * sizeof( float ) );

        for ( size_t i = 1; i < count; ++i )
        {
                float out[ 16 ];
                matrix::multiply( out, matrix, transformations[ i ]->getMatrix() );
                std::memcpy( matrix, out, 16 * sizeof( float ) );
        }

        dirty = true;
}