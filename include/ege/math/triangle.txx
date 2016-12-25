

template < typename T >
ege::math::Triangle< T >::Triangle( Vector< 3, T > const& v0, Vector< 3, T > const& v1, Vector< 3, T > const& v2 ):
        vertices( { v0, v1, v2 } )
{

}


template < typename T >
ege::math::Vector< 3, T >& ege::math::Triangle< T >::operator [] ( unsigned index )
{
        return vertices[ index ];
}


template < typename T >
ege::math::Vector< 3, T > const& ege::math::Triangle< T >::operator [] ( unsigned index ) const
{
        return vertices[ index ];
}


template < typename T >
ege::math::Vector< 3, T > ege::math::Triangle< T >::normal( bool clockWise ) const
{
        if ( clockWise )
                return ege::math::vector::crossProduct( vertices[ 2 ] - vertices[ 0 ], vertices[ 1 ] - vertices[ 0 ] ).normalized();
        else
                return ege::math::vector::crossProduct( vertices[ 1 ] - vertices[ 0 ], vertices[ 2 ] - vertices[ 0 ] ).normalized();
}
