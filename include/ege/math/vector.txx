#include <cmath>
#include <cstddef>


template < unsigned N, typename T >
ege::math::Vector< N, T >::Vector()
{
        for ( unsigned i = 0; i < N; ++i )
                raw[ i ] = 0;
}


template < unsigned N, typename T >
ege::math::Vector< N, T >::Vector( T ( & raw )[ N ] )
{
        for ( unsigned i = 0; i < N; ++i )
                this->raw[ i ] = raw[ i ];
}


template < unsigned N, typename T >
ege::math::Vector< N, T >::Vector( std::initializer_list< T > list )
{
        auto iterator = list.begin();

        for ( unsigned i = 0, n = std::min( ( std::size_t ) N, list.size() ); i < n; ++i )
                this->raw[ i ] = *iterator++;
}


template < unsigned N, typename T >
T ege::math::Vector< N, T >::length() const
{
        return std::sqrt( ege::math::vector::dotProduct( *this, *this ) );
}


template < unsigned N, typename T >
ege::math::Vector< N, T > ege::math::Vector< N, T >::normalized() const
{
        return ( 1 / length() ) * ( *this );
}


template < unsigned N, typename T >
T& ege::math::Vector< N, T >::operator [] ( unsigned index )
{
        return raw[ index ];
}


template < unsigned N, typename T >
T const& ege::math::Vector< N, T >::operator [] ( unsigned index ) const
{
        return raw[ index ];
}


template < unsigned N, typename T = float >
ege::math::Vector< N, T > ege::math::operator + ( ege::math::Vector< N, T > const& left, ege::math::Vector< N, T > const& right )
{
        T raw[ N ];

        for ( unsigned i = 0; i < N; ++i )
                raw[ i ] = left[ i ] + right[ i ];

        return ege::math::Vector< N, T >( raw );
}


template < unsigned N, typename T = float >
ege::math::Vector< N, T > ege::math::operator - ( ege::math::Vector< N, T > const& vector )
{
        T raw[ N ];

        for ( unsigned i = 0; i < N; ++i )
                raw[ i ] = -vector[ i ];

        return ege::math::Vector< N, T >( raw );
}


template < unsigned N, typename T = float >
ege::math::Vector< N, T > ege::math::operator - ( ege::math::Vector< N, T > const& left, ege::math::Vector< N, T > const& right )
{
        return left + ( -right );
}


template < unsigned N, typename T = float >
ege::math::Vector< N, T > ege::math::operator * ( T scalar, ege::math::Vector< N, T > const& vector )
{
        T raw[ N ];

        for ( unsigned i = 0; i < N; ++i )
                raw[ i ] = scalar * vector[ i ];

        return ege::math::Vector< N, T >( raw );
}


template < unsigned N, typename T = float >
ege::math::Vector< N, T > ege::math::operator * ( ege::math::Vector< N, T > const& vector, T scalar )
{
        return scalar * vector;
}


template < unsigned N, typename T = float >
ege::math::Vector< N, T > ege::math::operator / ( ege::math::Vector< N, T > const& vector, T scalar )
{
        return ( 1 / scalar ) * vector;
}


template < unsigned N, typename T = float >
T ege::math::vector::dotProduct( ege::math::Vector< N, T > const& left, ege::math::Vector< N, T > const& right )
{
        T sum = 0;

        for ( unsigned i = 0; i < N; ++i )
                sum += left[ i ] * right[ i ];

        return sum;
}


template < typename T = float >
ege::math::Vector< 3, T > ege::math::vector::crossProduct( ege::math::Vector< 3, T > const& left, ege::math::Vector< 3, T > const& right )
{
        T raw[ 3 ];
        raw[ 0 ] = left[ 1 ] * right[ 2 ] - left[ 2 ] * right[ 1 ];
        raw[ 1 ] = left[ 2 ] * right[ 0 ] - left[ 0 ] * right[ 2 ];
        raw[ 2 ] = left[ 0 ] * right[ 1 ] - left[ 1 ] * right[ 0 ];
        return ege::math::Vector< 3, T >( raw );
}
