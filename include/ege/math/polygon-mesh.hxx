

#ifndef EGE_MATH_POLYGONMESH_HXX
#define EGE_MATH_POLYGONMESH_HXX


#include <initializer_list>
#include <memory>
#include <ege/math/vector.hxx>


namespace ege
{
        namespace math
        {
                template < unsigned I = 3, unsigned N = 3, typename T = float >
                class PolygonMesh
                {
                        private:
                                std::shared_ptr< Vector< N, T > > vertices;
                                std::shared_ptr< std::array< unsigned, I > > indices;
                                const unsigned verticesCount;
                                const unsigned indicesCount;

                        public:
                                typedef const std::array< unsigned, I >* ConstIndicesIterator;

                                PolygonMesh( std::shared_ptr< Vector< N, T > > vertices, unsigned verticesCount, std::shared_ptr< std::array< unsigned, I > > indices, unsigned indicesCount );
                                PolygonMesh( std::initializer_list< Vector< N, T > > vertices, std::initializer_list< std::array< unsigned, I > > indices );
                                Vector< N, T >& operator [] ( unsigned index );
                                Vector< N, T > const& operator [] ( unsigned index ) const;
                                ConstIndicesIterator indicesBegin() const;
                                ConstIndicesIterator indicesEnd() const;
                };
        }
}


#include "polygon-mesh.txx"


#endif
