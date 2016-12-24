

template < unsigned H, unsigned W, typename T >
ege::math::Matrix< H, W, T >::Matrix()
{
        for ( unsigned h = 0; h < H; ++h )
                for ( unsigned w = 0; w < W; ++w )
                        this->raw[ h ][ w ] = 0;
}


template < unsigned H, unsigned W, typename T >
ege::math::Matrix< H, W, T >::Matrix( T ( & raw )[ H ][ W ] )
{
        for ( unsigned h = 0; h < H; ++h )
                for ( unsigned w = 0; w < W; ++w )
                        this->raw[ h ][ w ] = raw[ h ][ w ];
}


template < unsigned H, unsigned W, typename T >
T* ege::math::Matrix< H, W, T >::operator [] ( unsigned index )
{
        return raw[ index ];
}


template < unsigned H, unsigned W, typename T >
const T* ege::math::Matrix< H, W, T >::operator [] ( unsigned index ) const
{
        return raw[ index ];
}


template < unsigned M, unsigned N, unsigned P, typename T = float >
ege::math::Matrix< M, P, T > ege::math::operator * ( ege::math::Matrix< M, N, T > const& left, ege::math::Matrix< N, P, T > const& right )
{
        T raw[ M ][ P ];

        for ( unsigned i = 0; i < M; ++i )
        {
                for ( unsigned j = 0; j < P; ++j )
                {
                        T sum = 0;

                        for ( unsigned k = 0; k < N; ++k )
                                sum += left[ i ][ k ] * right[ k ][ j ];

                        raw[ i ][ j ] = sum;
                }
        }

        return ege::math::Matrix< M, P, T >( raw );
}
