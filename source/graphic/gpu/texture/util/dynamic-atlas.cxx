#include <ege/graphic/gpu/texture/util/dynamic-atlas.hxx>
#include <ege/exception.hxx>
#include <ege/engine.hxx>


using namespace ege;
using namespace ege::graphic::gpu;
using namespace ege::graphic::gpu::texture::util;


class Node
{
        private:
                Node** fragments;
                bool firstFragmentOwned;
                RectangularRegion* owner;

                void calculateFragmentsCoordinates( unsigned int x, unsigned int y, unsigned int width, unsigned int height,
                        unsigned int ( * coordinates )[ 2 ][ 4 ], bool ( * activeFragments )[ 4 ] );

                void fragmentUnsafe( Node* firstFragment );
                void fragment( Node* firstFragment );
                void fragment();
                void defragment();
                void setOwner( RectangularRegion* owner );
                void removeOwner();

        public:
                unsigned int const x;
                unsigned int const y;
                unsigned int const size;
                DynamicAtlas::NodesGroup* const nodes;

                Node( unsigned int x, unsigned int y, unsigned int size, DynamicAtlas::NodesGroup* nodes );
                ~Node();
                bool isFragmented() const;
                Node* getFirstFragment();
                bool isOwned() const;
                bool isUsed() const;
                const Node** getFragments() const;
                Node* searchFastly( unsigned int width, unsigned int height );
                void assign( RectangularRegion* owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                void unassign( unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                void insert( Node* node );
};


class DynamicAtlas::NodesGroup
{
        friend Node;

        private:
                unsigned int nodesCount;
                unsigned int minNodeSize;
                Node* root;

                void incrementSize( unsigned int size );
                void decrementSize( unsigned int size );

        public:
                NodesGroup( unsigned int rootSize, unsigned int minNodeSize );
                ~NodesGroup();
                void changeSize( unsigned int size );
                unsigned int canReduceSizeTo();
                Node* getRoot();
};


constexpr static unsigned int nextPowerOfTwo( unsigned int n )
{
        // Thanks to: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return n + 1;
}


void Node::calculateFragmentsCoordinates( unsigned int x, unsigned int y, unsigned int width, unsigned int height,
        unsigned int ( * coordinates )[ 2 ][ 4 ], bool ( * activeFragments )[ 4 ] )
{
        unsigned int half = size >> 1;
        bool left = x < half;
        bool right = x + width > half;
        bool bottom = y < half;
        bool top = y + height > half;

        ( *activeFragments )[ 0 ] = left && bottom;
        ( *activeFragments )[ 1 ] = left && top;
        ( *activeFragments )[ 2 ] = right && bottom;
        ( *activeFragments )[ 3 ] = right && top;

        if ( left )
        {
                ( *coordinates )[ 0 ][ 0 ] = x;

                if ( right )
                {
                        ( *coordinates )[ 0 ][ 2 ] = half - x;
                        ( *coordinates )[ 1 ][ 0 ] = 0;
                        ( *coordinates )[ 1 ][ 2 ] = width - ( *coordinates )[ 0 ][ 2 ];
                }
                else
                {
                        ( *coordinates )[ 0 ][ 2 ] = width;
                }
        }
        else
        {
                ( *coordinates )[ 1 ][ 0 ] = x - half;
                ( *coordinates )[ 1 ][ 2 ] = width;
        }

        if ( bottom )
        {
                ( *coordinates )[ 0 ][ 1 ] = y;

                if ( top )
                {
                        ( *coordinates )[ 0 ][ 3 ] = half - y;
                        ( *coordinates )[ 1 ][ 1 ] = 0;
                        ( *coordinates )[ 1 ][ 3 ] = height - ( *coordinates )[ 0 ][ 3 ];
                }
                else
                {
                        ( *coordinates )[ 0 ][ 3 ] = height;
                }
        }
        else
        {
                ( *coordinates )[ 1 ][ 1 ] = y - half;
                ( *coordinates )[ 1 ][ 3 ] = height;
        }
}


bool Node::isFragmented() const
{
        return fragments != nullptr;
}


void Node::fragmentUnsafe( Node* firstFragment )
{
        const unsigned int half = size >> 1;
        const unsigned int x1 = x + half;
        const unsigned int y1 = y + half;

        fragments = new Node*[ 4 ];
        fragments[ 0 ] = firstFragment;
        fragments[ 1 ] = new Node( x, y1, half, nodes );
        fragments[ 2 ] = new Node( x1, y, half, nodes );
        fragments[ 3 ] = new Node( x1, y1, half, nodes );
}


void Node::fragment( Node* firstFragment )
{
        if ( isFragmented() )
                return;

        fragmentUnsafe( firstFragment );
}


void Node::fragment()
{
        if ( isFragmented() )
                return;

        fragmentUnsafe( new Node( x, y, size >> 1, nodes ) );
}


void Node::defragment()
{
        if ( !isFragmented() )
                return;

        if ( firstFragmentOwned )
                delete fragments[ 0 ];

        delete fragments[ 1 ];
        delete fragments[ 2 ];
        delete fragments[ 3 ];
        delete fragments;
        fragments = nullptr;
}


Node* Node::getFirstFragment()
{
        return fragments[ 0 ];
}


void Node::setOwner( RectangularRegion* owner )
{
        this->owner = owner;
}


void Node::removeOwner()
{
        this->owner = nullptr;
}


bool Node::isOwned() const
{
        return owner != nullptr;
}


bool Node::isUsed() const
{
        return isFragmented() || isOwned();
}


const Node** Node::getFragments() const
{
        return const_cast< const Node** >( fragments );
}


Node* Node::searchFastly( unsigned int width, unsigned int height )
{
        const unsigned int half = size >> 1;

        if ( width > size || height > size )
                return nullptr;

        if ( !isFragmented() )
                return isOwned() ? nullptr : this;

        for ( uint8_t i = 0; i < 4; ++i )
        {
                Node* result = fragments[ i ]->searchFastly( width, height );

                if ( result != nullptr )
                        return result;
        }

        return nullptr;
}


void Node::assign( RectangularRegion* owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
        if ( ( size == width && size == height ) || size == nodes->minNodeSize )
        {
                this->owner = owner;
                return;
        }

        fragment();

        unsigned int coordinates[ 2 ][ 4 ];
        bool activeFragments[ 4 ];
        calculateFragmentsCoordinates( x, y, width, height, &coordinates, &activeFragments );

        if ( activeFragments[ 0 ] )
                fragments[ 0 ]->assign( owner, coordinates[ 0 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 0 ][ 3 ] );

        if ( activeFragments[ 1 ] )
                fragments[ 1 ]->assign( owner, coordinates[ 0 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 1 ][ 3 ] );

        if ( activeFragments[ 2 ] )
                fragments[ 2 ]->assign( owner, coordinates[ 1 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 0 ][ 3 ] );

        if ( activeFragments[ 3 ] )
                fragments[ 3 ]->assign( owner, coordinates[ 1 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 1 ][ 3 ] );
}


void Node::unassign( unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
        if ( !isFragmented() )
        {
                removeOwner();
                return;
        }

        unsigned int coordinates[ 2 ][ 4 ];
        bool activeFragments[ 4 ];
        calculateFragmentsCoordinates( x, y, width, height, &coordinates, &activeFragments );

        if ( activeFragments[ 0 ] )
                fragments[ 0 ]->unassign( coordinates[ 0 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 0 ][ 3 ] );

        if ( activeFragments[ 1 ] )
                fragments[ 1 ]->unassign( coordinates[ 0 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 1 ][ 3 ] );

        if ( activeFragments[ 2 ] )
                fragments[ 2 ]->unassign( coordinates[ 1 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 0 ][ 3 ] );

        if ( activeFragments[ 3 ] )
                fragments[ 3 ]->unassign( coordinates[ 1 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 1 ][ 3 ] );

        if ( !fragments[ 0 ]->isUsed() && !fragments[ 1 ]->isUsed() && !fragments[ 2 ]->isUsed() && !fragments[ 3 ]->isUsed() )
                defragment();
}


void Node::insert( Node* node )
{
        if ( size >> 1 == node->size )
        {
                fragment( node );
        }
        else
        {
                fragment();
                fragments[ 0 ]->insert( node );
        }
}


Node::Node( unsigned int x, unsigned int y, unsigned int size, DynamicAtlas::NodesGroup* nodes ):
        x( x ), y( y ), size( size ), nodes( nodes ), fragments( nullptr ), firstFragmentOwned( true ), owner( nullptr )
{
        ++nodes->nodesCount;
}


Node::~Node()
{
        defragment();
        --nodes->nodesCount;
}


void DynamicAtlas::NodesGroup::incrementSize( unsigned int size )
{
        Node* newRoot = new Node( 0, 0, size, this );
        newRoot->insert( root );
        root = newRoot;
}


void DynamicAtlas::NodesGroup::decrementSize( unsigned int size )
{
        Node* newRoot = root;

        while ( newRoot->size != size )
        {
                if ( !newRoot->isFragmented() )
                {
                        delete newRoot;
                        root = new Node( 0, 0, size, this );
                        return;
                }

                Node* firstFragment = newRoot->getFirstFragment();
                delete newRoot;
                newRoot = firstFragment;
        }

        root = newRoot;
}


DynamicAtlas::NodesGroup::NodesGroup( unsigned int rootSize, unsigned int minNodeSize ):
        root( new Node( 0, 0, rootSize, this ) ), minNodeSize( minNodeSize ), nodesCount( 0 )
{

}


DynamicAtlas::NodesGroup::~NodesGroup()
{
        delete root;

        if ( nodesCount != 0 )
                ege::engine::resources->logger->log(
                        ege::util::log::Level::WARNING,
                        "memory leak detected in nodes of texture dynamic atlas: %d nodes (%d bytes)",
                        nodesCount, sizeof( Node ) + ( nodesCount - 1 ) * ( sizeof( Node ) + sizeof( Node* ) ) );
}


void DynamicAtlas::NodesGroup::changeSize( unsigned int size )
{
        if ( root->size == size )
                return;

        if ( root->size < size )
                incrementSize( size );
        else
                decrementSize( size );
}


unsigned int DynamicAtlas::NodesGroup::canReduceSizeTo()
{
        const Node* node = const_cast< const Node* >( root );

        while ( true )
        {
                const Node** fragments = node->getFragments();

                if ( !node->isFragmented() || fragments[ 1 ]->isUsed() || fragments[ 2 ]->isUsed() || fragments[ 3 ]->isUsed() )
                        break;

                node = fragments[ 0 ];
        }

        return node->isUsed() ? node->size : 0;
}


Node* DynamicAtlas::NodesGroup::getRoot()
{
        return root;
}


void DynamicAtlas::clear()
{
        if ( nodes != nullptr )
        {
                delete nodes;
                nodes = nullptr;
        }

        if ( texture != nullptr )
        {
                delete texture;
                texture = nullptr;
        }

        if ( regions.size() != 0 )
        {
                for ( auto region : regions )
                        delete region;

                regions.clear();
        }
}


void DynamicAtlas::reset()
{
        clear();
        texture = new Texture2D( edgeThreshold, edgeThreshold );
        edgeSize = edgeThreshold;
        totalPixels = edgeThreshold * edgeThreshold;
        usedPixels = 0;
        nodes = new NodesGroup( edgeThreshold, 2 );
}


void DynamicAtlas::changeEdgeSize( unsigned int size )
{
        if ( size == edgeSize )
                return;

        nodes->changeSize( size );
        texture->resize( size, size, true );
        edgeSize = size;
        totalPixels = size * size;

        for ( auto region : regions )
                region->recalculateUV();
}


DynamicAtlas::DynamicAtlas( unsigned int edgeThreshold )
{
        edgeThreshold = nextPowerOfTwo( edgeThreshold );
        static const unsigned int minimumEdgeThreshold = 32;
        this->edgeThreshold = ( edgeThreshold < minimumEdgeThreshold ) ? minimumEdgeThreshold : edgeThreshold;
        texture = nullptr;
        nodes = nullptr;
        reset();
}


DynamicAtlas::~DynamicAtlas()
{
        clear();
}


const RectangularRegion* DynamicAtlas::insert( const ImageBuffer& imageBuffer )
{
        unsigned int width = imageBuffer.width;
        unsigned int height = imageBuffer.height;

        const Node* suitable;

        if ( ( width * height + usedPixels > totalPixels )
                || ( ( suitable = nodes->getRoot()->searchFastly( width, height ) ) == nullptr ) )
        {
                unsigned int max = ( width < height ) ? height : width;
                changeEdgeSize( 2 * nextPowerOfTwo( max ) );
                suitable = nodes->getRoot()->getFragments()[ 1 ];
        }

        RectangularRegion* region = new RectangularRegion( *texture, suitable->x, suitable->y, width, height );
        nodes->getRoot()->assign( region, suitable->x, suitable->y, width, height );
        texture->substitute( suitable->x, suitable->y, imageBuffer );
        usedPixels += region->width * region->height;
        regions.insert( region );
        return region;
}


void DynamicAtlas::remove( const RectangularRegion* region )
{
        if ( regions.erase( const_cast< RectangularRegion* >( region ) ) == 0 )
                Exception::throwNew( "invalid argument: specified region is not contained in atlas (or no more)" );

        usedPixels -= region->width * region->height;
        nodes->getRoot()->unassign( region->x, region->y, region->width, region->height );

        unsigned int canBeReducedTo = nodes->canReduceSizeTo();
        canBeReducedTo = canBeReducedTo < edgeThreshold ? edgeThreshold : canBeReducedTo;
        changeEdgeSize( canBeReducedTo );
}


void DynamicAtlas::removeAll()
{
        reset();
}


const texture::Texture2D& DynamicAtlas::getTexture()
{
        return *texture;
}
