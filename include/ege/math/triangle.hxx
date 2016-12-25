

#ifndef EGE_MATH_TRIANGLE_HXX
#define EGE_MATH_TRIANGLE_HXX


#include <ege/math/vector.hxx>


namespace ege
{
        namespace math
        {
                template < typename T = float >
                class Triangle
                {
                        private:
                                Vector< 3, T > vertices[ 3 ];

                        public:
                                Triangle( Vector< 3, T > const& v0, Vector< 3, T > const& v1, Vector< 3, T > const& v2 );
                                Vector< 3, T >& operator [] ( unsigned index );
                                Vector< 3, T > const& operator [] ( unsigned index ) const;
                                Vector< 3, T > normal( bool clockWise = true ) const;
                };
        }
}


#include "triangle.txx"


#endif
