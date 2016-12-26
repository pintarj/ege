


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
