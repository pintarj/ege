

#ifndef EGE_PRIVATE_GRAPHIC_GEOMETRY_MATRIX_HXX
#define EGE_PRIVATE_GRAPHIC_GEOMETRY_MATRIX_HXX


namespace ege_private
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
                        }
                }
        }
}


#endif
