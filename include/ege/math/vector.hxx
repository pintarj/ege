

#ifndef EGE_MATH_VECTOR_HXX
#define EGE_MATH_VECTOR_HXX


#include <initializer_list>


namespace ege
{
        namespace math
        {
                template < unsigned N = 3, typename T = float >
                class Vector
                {
                        private:
                                T raw[ N ];

                        public:
                                Vector();
                                Vector( T ( & raw )[ N ] );
                                Vector( std::initializer_list< T > list );
                                T length() const;
                                Vector< N, T > normalized() const;
                                T& operator [] ( unsigned index );
                                T const& operator [] ( unsigned index ) const;
                };

                template < unsigned N, typename T = float >
                Vector< N, T > operator + ( Vector< N, T > const& left, Vector< N, T > const& right );

                template < unsigned N, typename T = float >
                Vector< N, T > operator - ( Vector< N, T > const& vector );

                template < unsigned N, typename T = float >
                Vector< N, T > operator - ( Vector< N, T > const& left, Vector< N, T > const& right );

                template < unsigned N, typename T = float >
                Vector< N, T > operator * ( T scalar, Vector< N, T > const& vector );

                template < unsigned N, typename T = float >
                Vector< N, T > operator * ( Vector< N, T > const& vector, T scalar );

                template < unsigned N, typename T = float >
                Vector< N, T > operator / ( Vector< N, T > const& vector, T scalar );

                namespace vector
                {
                        template < unsigned N, typename T = float >
                        T dotProduct( Vector< N, T > const& left, Vector< N, T > const& right );

                        template < typename T = float >
                        Vector< 3, T > crossProduct( Vector< 3, T > const& left, Vector< 3, T > const& right );
                }
        }
}


#include "vector.txx"


#endif
