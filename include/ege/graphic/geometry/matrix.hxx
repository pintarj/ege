

#ifndef EGE_GRAPHIC_GEOMETRY_MATRIX_HXX
#define EGE_GRAPHIC_GEOMETRY_MATRIX_HXX


#include <cmath>


namespace ege
{
        namespace graphic
        {
                namespace geometry
                {
                        namespace matrix
                        {
                                static inline void multiply( float* out, const float* left, const float* right )
                                {
                                        out[  0 ] = ( left[  0 ] * right[  0 ] ) + ( left[  4 ] * right[  1 ] ) + ( left[  8 ] * right[  2 ] ) + ( left[ 12 ] * right[  3 ] );
                                        out[  4 ] = ( left[  0 ] * right[  4 ] ) + ( left[  4 ] * right[  5 ] ) + ( left[  8 ] * right[  6 ] ) + ( left[ 12 ] * right[  7 ] );
                                        out[  8 ] = ( left[  0 ] * right[  8 ] ) + ( left[  4 ] * right[  9 ] ) + ( left[  8 ] * right[ 10 ] ) + ( left[ 12 ] * right[ 11 ] );
                                        out[ 12 ] = ( left[  0 ] * right[ 12 ] ) + ( left[  4 ] * right[ 13 ] ) + ( left[  8 ] * right[ 14 ] ) + ( left[ 12 ] * right[ 15 ] );
                                        out[  1 ] = ( left[  1 ] * right[  0 ] ) + ( left[  5 ] * right[  1 ] ) + ( left[  9 ] * right[  2 ] ) + ( left[ 13 ] * right[  3 ] );
                                        out[  5 ] = ( left[  1 ] * right[  4 ] ) + ( left[  5 ] * right[  5 ] ) + ( left[  9 ] * right[  6 ] ) + ( left[ 13 ] * right[  7 ] );
                                        out[  9 ] = ( left[  1 ] * right[  8 ] ) + ( left[  5 ] * right[  9 ] ) + ( left[  9 ] * right[ 10 ] ) + ( left[ 13 ] * right[ 11 ] );
                                        out[ 13 ] = ( left[  1 ] * right[ 12 ] ) + ( left[  5 ] * right[ 13 ] ) + ( left[  9 ] * right[ 14 ] ) + ( left[ 13 ] * right[ 15 ] );
                                        out[  2 ] = ( left[  2 ] * right[  0 ] ) + ( left[  6 ] * right[  1 ] ) + ( left[ 10 ] * right[  2 ] ) + ( left[ 14 ] * right[  3 ] );
                                        out[  6 ] = ( left[  2 ] * right[  4 ] ) + ( left[  6 ] * right[  5 ] ) + ( left[ 10 ] * right[  6 ] ) + ( left[ 14 ] * right[  7 ] );
                                        out[ 10 ] = ( left[  2 ] * right[  8 ] ) + ( left[  6 ] * right[  9 ] ) + ( left[ 10 ] * right[ 10 ] ) + ( left[ 14 ] * right[ 11 ] );
                                        out[ 14 ] = ( left[  2 ] * right[ 12 ] ) + ( left[  6 ] * right[ 13 ] ) + ( left[ 10 ] * right[ 14 ] ) + ( left[ 14 ] * right[ 15 ] );
                                        out[  3 ] = ( left[  3 ] * right[  0 ] ) + ( left[  7 ] * right[  1 ] ) + ( left[ 11 ] * right[  2 ] ) + ( left[ 15 ] * right[  3 ] );
                                        out[  7 ] = ( left[  3 ] * right[  4 ] ) + ( left[  7 ] * right[  5 ] ) + ( left[ 11 ] * right[  6 ] ) + ( left[ 15 ] * right[  7 ] );
                                        out[ 11 ] = ( left[  3 ] * right[  8 ] ) + ( left[  7 ] * right[  9 ] ) + ( left[ 11 ] * right[ 10 ] ) + ( left[ 15 ] * right[ 11 ] );
                                        out[ 15 ] = ( left[  3 ] * right[ 12 ] ) + ( left[  7 ] * right[ 13 ] ) + ( left[ 11 ] * right[ 14 ] ) + ( left[ 15 ] * right[ 15 ] );
                                }

                                static inline void identity( float* matrix )
                                {
                                        matrix[  0 ] = 1.0f;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = 1.0f;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = 1.0f;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void scale( float* matrix, float x, float y, float z )
                                {
                                        matrix[  0 ] = x;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = y;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = z;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void translate( float* matrix, float x, float y, float z )
                                {
                                        matrix[  0 ] = 1.0f;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = 1.0f;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = 1.0f;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = x;
                                        matrix[ 13 ] = y;
                                        matrix[ 14 ] = z;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void rotateX( float* matrix, float radians )
                                {
                                        float sin       = sinf( radians );
                                        float cos       = cosf( radians );

                                        matrix[  0 ] = 1.0f;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = cos;
                                        matrix[  6 ] = sin;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = -sin;
                                        matrix[ 10 ] = cos;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void rotateY( float* matrix, float radians )
                                {
                                        float sin       = sinf( radians );
                                        float cos       = cosf( radians );

                                        matrix[  0 ] = cos;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = -sin;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = 1.0f;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = sin;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = cos;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void rotateZ( float* matrix, float radians )
                                {
                                        float sin       = sinf( radians );
                                        float cos       = cosf( radians );

                                        matrix[  0 ] = cos;
                                        matrix[  1 ] = sin;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = -sin;
                                        matrix[  5 ] = cos;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = 1.0f;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void rotate( float* matrix, float radians, float x, float y, float z )
                                {
                                        float sin       = std::sin( radians );
                                        float cos       = std::cos( radians );
                                        float mcos      = 1.0f - cos;
                                        float xmcos     = x * mcos;
                                        float ymcos     = y * mcos;
                                        float zmcos     = z * mcos;
                                        float xymcos    = x * ymcos;
                                        float yzmcos    = y * zmcos;
                                        float zxmcos    = z * xmcos;
                                        float xsin      = x * sin;
                                        float ysin      = y * sin;
                                        float zsin      = z * sin;

                                        matrix[  0 ] = x * xmcos + cos;
                                        matrix[  1 ] = xymcos + zsin;
                                        matrix[  2 ] = zxmcos - ysin;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = xymcos - zsin;
                                        matrix[  5 ] = y * ymcos + cos;
                                        matrix[  6 ] = yzmcos + xsin;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = zxmcos + ysin;
                                        matrix[  9 ] = yzmcos - xsin;
                                        matrix[ 10 ] = z * zmcos + cos;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void ortho( float* matrix, float left, float right, float bottom, float top, float near, float far )
                                {
                                        float rml = right - left;
                                        float tmb = top - bottom;
                                        float fmn = far - near;

                                        matrix[  0 ] = 2.0f / rml;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = 2.0f / tmb;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = -2.0f / fmn;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = -( ( right + left ) / rml );
                                        matrix[ 13 ] = -( ( top + bottom ) / tmb );
                                        matrix[ 14 ] = -( ( far + near ) / fmn );
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void ortho2D( float* matrix, float left, float right, float bottom, float top )
                                {
                                        float rml = right - left;
                                        float tmb = top - bottom;

                                        matrix[  0 ] = 2.0f / rml;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;

                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = 2.0f / tmb;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;

                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = -1.0f;
                                        matrix[ 11 ] = 0.0f;

                                        matrix[ 12 ] = -( ( right + left ) / rml );
                                        matrix[ 13 ] = -( ( top + bottom ) / tmb );
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void fromOriginLookAt( float* matrix, float centerX, float centerY, float centerZ, float upX, float upY, float upZ )
                                {
                                        float icl = 1.0f / std::sqrt( ( centerX * centerX ) + ( centerY * centerY ) + ( centerZ * centerZ ) );
                                        float ncx = centerX * icl;
                                        float ncy = centerY * icl;
                                        float ncz = centerZ * icl;
                                        float mx0 = ( ncy * upZ ) - ( ncz * upY );
                                        float mx4 = ( ncz * upX ) - ( ncx * upZ );
                                        float mx8 = ( ncx * upY ) - ( ncy * upX );
                                        float isl = 1.0f / std::sqrt( ( mx0 * mx0 ) + ( mx4 * mx4 ) + ( mx8 * mx8 ) );
                                        float snX = mx0 * isl;
                                        float snY = mx4 * isl;
                                        float snZ = mx8* isl;

                                        matrix[  0 ] = mx0;
                                        matrix[  1 ] = ( snY * ncz ) - ( snZ * ncy );
                                        matrix[  2 ] = -ncx;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = mx4;
                                        matrix[  5 ] = ( snZ * ncx ) - ( snX * ncz );
                                        matrix[  6 ] = -ncy;
                                        matrix[  8 ] = mx8;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  9 ] = ( snX * ncy ) - ( snY * ncx );
                                        matrix[ 10 ] = -ncz;
                                        matrix[ 11 ] = 0.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = 0.0f;
                                        matrix[ 15 ] = 1.0f;
                                }

                                static inline void lookAt( float* matrix, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ )
                                {
                                        float buffer[ 32 ];
                                        fromOriginLookAt( &buffer[ 0 ], centerX, centerY, centerZ, upX, upY, upZ );
                                        translate( &buffer[ 16 ], -eyeX, -eyeY, -eyeZ );
                                        multiply( matrix, &buffer[ 0 ], &buffer[ 16 ] );
                                }

                                static inline void frustum( float* matrix, float left, float right, float bottom, float top, float near, float far )
                                {
                                        float rml = right - left;
                                        float tmb = top - bottom;
                                        float fmn = far - near;
                                        float n2 = 2.0f * near;

                                        matrix[  0 ] = n2 / rml;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;
                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = n2 / tmb;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;
                                        matrix[  8 ] = ( right + left ) / rml;
                                        matrix[  9 ] = ( top + bottom ) / tmb;
                                        matrix[ 10 ] = -( ( far + near ) / fmn );
                                        matrix[ 11 ] = -1.0f;
                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = -( ( n2 * far ) / fmn );
                                        matrix[ 15 ] = 0.0f;
                                }

                                void perspective( float* matrix, float degree, float ratio, float near, float far )
                                {
                                        float radians   = degree * ( M_PI / 180.0f );
                                        float f         = 1.0f / std::tan( radians / 2.0f );
                                        float d         = near - far;

                                        matrix[  0 ] = f / ratio;
                                        matrix[  1 ] = 0.0f;
                                        matrix[  2 ] = 0.0f;
                                        matrix[  3 ] = 0.0f;

                                        matrix[  4 ] = 0.0f;
                                        matrix[  5 ] = f;
                                        matrix[  6 ] = 0.0f;
                                        matrix[  7 ] = 0.0f;

                                        matrix[  8 ] = 0.0f;
                                        matrix[  9 ] = 0.0f;
                                        matrix[ 10 ] = ( far + near ) / d;
                                        matrix[ 11 ] = -1.0f;

                                        matrix[ 12 ] = 0.0f;
                                        matrix[ 13 ] = 0.0f;
                                        matrix[ 14 ] = ( 2.0f * far * near ) / d;
                                        matrix[ 15 ] = 0.0f;
                                }
                        }
                }
        }
}


#endif
