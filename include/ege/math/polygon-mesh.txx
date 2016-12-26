


template < unsigned I, unsigned N, typename T >
ege::math::PolygonMesh< I, N, T >::PolygonMesh( std::shared_ptr< Vector< N, T > > vertices, unsigned verticesCount, std::shared_ptr< std::array< unsigned, I > > indices, unsigned indicesCount ):
        vertices( vertices ),
        verticesCount( verticesCount ),
        indices( indices ),
        indicesCount( indicesCount )
{

}


template < unsigned I, unsigned N, typename T >
ege::math::PolygonMesh< I, N, T >::PolygonMesh( std::initializer_list< Vector< N, T > > vertices, std::initializer_list< std::array< unsigned, I > > indices ):
        vertices( new ege::math::Vector< N, T >[ vertices.size() ] ),
        verticesCount( vertices.size() ),
        indices( new std::array< unsigned, I >[ indices.size() ] ),
        indicesCount( indices.size() )
{
        auto verticesIterator = vertices.begin();

        for ( unsigned i = 0; i < verticesCount; ++i )
                ( *this->vertices )[ i ] = *verticesIterator++;

        auto indicesIterator = indices.begin();

        for ( unsigned i = 0; i < indicesCount; ++i )
                ( *this->indices )[ i ] = *indicesIterator++;
}


template < unsigned I, unsigned N, typename T >
unsigned ege::math::PolygonMesh< I, N, T >::getVerticesCount() const
{
        return verticesCount;
}


template < unsigned I, unsigned N, typename T >
unsigned ege::math::PolygonMesh< I, N, T >::getIndicesCount() const
{
        return indicesCount;
}


template < unsigned I, unsigned N, typename T >
ege::math::Vector< N, T >& ege::math::PolygonMesh< I, N, T >::operator [] ( unsigned index )
{
        return vertices.get()[ index ];
}


template < unsigned I, unsigned N, typename T >
ege::math::Vector< N, T > const& ege::math::PolygonMesh< I, N, T >::operator [] ( unsigned index ) const
{
        return vertices.get()[ index ];
}


template < unsigned I, unsigned N, typename T >
const std::array< unsigned, I >* ege::math::PolygonMesh< I, N, T >::indicesBegin() const
{
        return &( indices.get() )[ 0 ];
}


template < unsigned I, unsigned N, typename T >
const std::array< unsigned, I >* ege::math::PolygonMesh< I, N, T >::indicesEnd() const
{
        return &( indices.get() )[ indicesCount ];
}


template < typename T >
std::shared_ptr< ege::math::PolygonMesh< 3, 3, T > > ege::math::polygonMesh::icoSphere( unsigned levelOfDetail, T length )
{
        std::function< unsigned( unsigned ) > finalVerticesCount = [ & ] ( unsigned lot )
                {
                        if ( lot == 0 )
                                return ( unsigned ) 12;
                        else
                                return ( unsigned ) ( finalVerticesCount( lot - 1 ) + ( 30 << ( ( lot - 1 ) << 1 ) ) );
                };

        const unsigned verticesCount = finalVerticesCount( levelOfDetail );
        unsigned indicesCount = 20;
        unsigned index = 12;
        std::shared_ptr< ege::math::Vector< 3, T > > vertices( new ege::math::Vector< 3, T >[ verticesCount ] );
        std::shared_ptr< std::array< unsigned, 3 > > indices( new std::array< unsigned, 3 >[ indicesCount ] );
        std::map< std::pair< unsigned, unsigned >, unsigned > cache;
        const T l0 = ( T ) 0.5257311121191336;
        const T l1 = ( T ) 0.85065080835204;

        vertices.get()[  0 ] = { -l0, +l1, 0 };
        vertices.get()[  1 ] = { +l0, +l1, 0 };
        vertices.get()[  2 ] = { -l0, -l1, 0 };
        vertices.get()[  3 ] = { +l0, -l1, 0 };

        vertices.get()[  4 ] = { 0, -l0, +l1 };
        vertices.get()[  5 ] = { 0, +l0, +l1 };
        vertices.get()[  6 ] = { 0, -l0, -l1 };
        vertices.get()[  7 ] = { 0, +l0, -l1 };

        vertices.get()[  8 ] = { +l1, 0, -l0 };
        vertices.get()[  9 ] = { +l1, 0, +l0 };
        vertices.get()[ 10 ] = { -l1, 0, -l0 };
        vertices.get()[ 11 ] = { -l1, 0, +l0 };

        indices.get()[  0 ] = { 0, 11, 5 };
        indices.get()[  1 ] = { 0, 5, 1 };
        indices.get()[  2 ] = { 0, 1, 7 };
        indices.get()[  3 ] = { 0, 7, 10 };
        indices.get()[  4 ] = { 0, 10, 11 };

        indices.get()[  5 ] = { 1, 5, 9 };
        indices.get()[  6 ] = { 5, 11, 4 };
        indices.get()[  7 ] = { 11, 10, 2 };
        indices.get()[  8 ] = { 10, 7, 6 };
        indices.get()[  9 ] = { 7, 1, 8 };

        indices.get()[ 10 ] = { 3, 9, 4 };
        indices.get()[ 11 ] = { 3, 4, 2 };
        indices.get()[ 12 ] = { 3, 2, 6 };
        indices.get()[ 13 ] = { 3, 6, 8 };
        indices.get()[ 14 ] = { 3, 8, 9 };

        indices.get()[ 15 ] = { 4, 9, 5 };
        indices.get()[ 16 ] = { 2, 4, 11 };
        indices.get()[ 17 ] = { 6, 2, 10 };
        indices.get()[ 18 ] = { 8, 6, 7 };
        indices.get()[ 19 ] = { 9, 8, 1 };

        std::function< unsigned( unsigned, unsigned ) > getMiddleIndex = [ & ] ( unsigned index0, unsigned index1 )
                {
                        unsigned min;
                        unsigned max;

                        if ( index0 < index1 )
                        {
                                min = index0;
                                max = index1;
                        }
                        else
                        {
                                min = index1;
                                max = index0;
                        }

                        std::pair< unsigned, unsigned > key( min, max );
                        auto iterator = cache.find( key );

                        if ( iterator != cache.end() )
                                return iterator->second;

                        cache[ key ] = index;
                        auto& v0 = vertices.get()[ min ];
                        auto& v1 = vertices.get()[ max ];
                        vertices.get()[ index ] = ( ( v0 + v1 ) / ( T ) 2.0 ).normalized();
                        return index++;
                };

        for ( unsigned level = 0; level < levelOfDetail; ++level )
        {
                unsigned newIndicesCount = indicesCount << 2;
                std::shared_ptr< std::array< unsigned, 3 > > newIndices( new std::array< unsigned, 3 >[ newIndicesCount ] );
                std::array< unsigned, 3 >* ptr = newIndices.get();

                for ( unsigned i = 0; i < indicesCount; ++i )
                {
                        std::array< unsigned, 3 > const& triangle = indices.get()[ i ];
                        unsigned i0 = getMiddleIndex( triangle[ 0 ], triangle[ 1 ] );
                        unsigned i1 = getMiddleIndex( triangle[ 1 ], triangle[ 2 ] );
                        unsigned i2 = getMiddleIndex( triangle[ 2 ], triangle[ 0 ] );

                        *ptr++ = { triangle[ 0 ], i0, i2 };
                        *ptr++ = { triangle[ 1 ], i1, i0 };
                        *ptr++ = { triangle[ 2 ], i2, i1 };
                        *ptr++ = { i0, i1, i2 };
                }

                indicesCount = newIndicesCount;
                indices = newIndices;
        }

        if ( length != ( T ) 1.0 )
        {
                for ( unsigned i = 0; i < verticesCount; ++i )
                        vertices.get()[ i ] = length * vertices.get()[ i ];
        }

        return std::shared_ptr< ege::math::PolygonMesh< 3, 3, T > >( new ege::math::PolygonMesh< 3, 3, T >( vertices, verticesCount, indices, indicesCount ) );
}
