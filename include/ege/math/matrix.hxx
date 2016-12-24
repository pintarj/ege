

#ifndef EGE_MATH_MATRIX_HXX
#define EGE_MATH_MATRIX_HXX


namespace ege
{
        namespace math
        {
                template < unsigned M, unsigned N = M, typename T = float >
                class Matrix
                {
                        private:
                                T raw[ M ][ N ];

                        public:
                                Matrix();
                                Matrix( T ( & raw )[ M ][ N ] );
                                T* operator [] ( unsigned index );
                                const T* operator [] ( unsigned index ) const;
                };

                template < unsigned M, unsigned N, unsigned P, typename T = float >
                Matrix< M, P, T > operator * ( Matrix< M, N, T > const& left, Matrix< N, P, T > const& right );
        }
}


#include "matrix.txx"


#endif
