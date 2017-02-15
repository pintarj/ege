#include <ege/graphic/gpu/texture/util/dynamic-atlas.hxx>
#include <ege/exception.hxx>
#include <ege/engine.hxx>
#include <cstring>


using namespace ege;
using namespace ege::graphic::gpu;
using namespace ege::graphic::gpu::texture::util;


class Node
{
        private:
                Node** fragments;
                bool firstFragmentOwned;
                RectangularRegion* owner;
                unsigned int freePixels;

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
                void assign( RectangularRegion* owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                void unassign( unsigned int x, unsigned int y, unsigned int width, unsigned int height );
                void insert( Node* node );
                unsigned int getFreePixels() const;
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


constexpr static unsigned int nextRepetitionOf( unsigned int value, unsigned int m )
{
        unsigned int mod = value % m;

        if ( mod == 0 )
                return value;
        else
                return value + m - mod;
}


constexpr static unsigned int calculateStartLevel( unsigned int w, unsigned int h, unsigned int rootSize )
{
        unsigned int value = ( rootSize * rootSize ) / ( w * h * 64 );
        unsigned int log = 0;

        while ( true )
        {
                if ( value == 0 )
                        break;

                value >>= 2;
                ++log;
        }

        return log;
}


static void fillUsageImage( bool* image, unsigned int width, unsigned int unit, const Node* node, const Node* origin )
{
        if ( node->size == unit || !node->isFragmented() )
        {
                if ( !node->isUsed() )
                        return;

                unsigned int limit = node->size / unit;
                unsigned int relX = ( node->x - origin->x ) / unit;
                unsigned int relY = ( node->y - origin->y ) / unit;

                for ( int i = 0; i < limit; ++i )
                        for ( int j = 0; j < limit; ++j )
                                image[ width * ( relY + i ) + relX + j ] = true;
        }
        else
        {
                const Node** fragments = node->getFragments();

                for ( uint8_t i = 0; i < 4; ++i )
                        fillUsageImage( image, width, unit, fragments[ i ], origin );
        }
}


static bool* getUsageImage( const Node* node, unsigned int level, unsigned int* dimensions )
{
        unsigned int unit = node->size >> level;
        unsigned int unitsPerSize = node->size / unit;
        size_t size = unitsPerSize * unitsPerSize;
        bool* image = new bool[ size ];
        memset( image, 0, size );
        dimensions[ 0 ] = unitsPerSize;
        dimensions[ 1 ] = unitsPerSize;
        fillUsageImage( image, unitsPerSize, unit, node, node );
        return image;
}


static bool calculateSolutions( bool* image, unsigned int* dimensions, int w, int h, unsigned int* solution )
{
        unsigned int solW = dimensions[ 0 ] + 1 - w;
        unsigned int* sums = new unsigned int[ dimensions[ 1 ] * solW ];
        memset( sums, 0, dimensions[ 1 ] * solW * 4 );

        for ( int y = 0; y < dimensions[ 1 ]; ++y )
        {
                bool* row = &image[ y * dimensions[ 0 ] ];
                unsigned int* sumsRow = &sums[ y * solW ];
                unsigned int rowSum = 0;

                for ( int x = 0, limit = w - 1; x < limit; ++x )
                        if ( row[ x ] )
                                ++rowSum;

                for ( int x = 0; x < solW; ++x )
                {
                        if ( row[ x + w - 1 ] )
                                ++rowSum;

                        sumsRow[ x ] = rowSum;

                        if ( row[ x ] )
                                --rowSum;
                }
        }

        for ( unsigned int x = 0; x < solW; ++x )
        {
                unsigned int lastY = 0;
                unsigned int count = 0;

                for ( unsigned int y = 0; y < dimensions[ 1 ]; ++y )
                {
                        if ( sums[ y * solW + x ] == 0 )
                        {
                                ++count;

                                if ( count == h )
                                        break;
                        }
                        else
                        {
                                lastY = y + 1;
                                count = 0;
                        }
                }

                if ( count == h )
                {
                        solution[ 0 ] = x;
                        solution[ 1 ] = lastY;
                        delete[] sums;
                        return true;
                }
        }

        delete[] sums;
        return false;
}


static bool searchNLevelsDeeper( unsigned int w, unsigned int h, const Node* node, unsigned int deeper, unsigned int* solution, unsigned int minUnitSize )
{
        if ( node->getFreePixels() < ( w * h ) )
                return false;

        if ( deeper != 0 )
        {
                if ( node->isOwned() )
                        return false;

                if ( node->isFragmented() )
                {
                        const Node** fragments = node->getFragments();
                        unsigned int deeperLevel = deeper - 1;

                        for ( uint8_t i = 0; i < 4; ++i )
                                if ( searchNLevelsDeeper( w, h, fragments[ i ], deeperLevel, solution, minUnitSize ) )
                                        return true;
                }
                else
                {
                        solution[ 0 ] = node->x;
                        solution[ 1 ] = node->y;
                        return true;
                }
        }
        else
        {
                for ( unsigned int level = 0; true; ++level )
                {
                        unsigned int unit = node->size >> level;
                        unsigned int leveledW = w / unit + ( ( w % unit != 0 ) ? 1 : 0 );
                        unsigned int leveledH = h / unit + ( ( h % unit != 0 ) ? 1 : 0 );
                        unsigned int dimensions[ 2 ];
                        bool* image = getUsageImage( node, level, dimensions );
                        bool solutionFound = calculateSolutions( image, dimensions, leveledW, leveledH, solution );
                        delete[] image;

                        if ( !solutionFound )
                        {
                                if ( unit == minUnitSize )
                                        return false;
                                else
                                        continue;
                        }

                        unsigned int solX = node->x + solution[ 0 ] * unit;
                        unsigned int solY = node->y + solution[ 1 ] * unit;
                        solution[ 0 ] = solX;
                        solution[ 1 ] = solY;
                        return true;
                }
        }

        return false;
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
        delete[] fragments;
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


void Node::assign( RectangularRegion* owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
        freePixels -= width * height;

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


unsigned int Node::getFreePixels() const
{
        return freePixels;
}


Node::Node( unsigned int x, unsigned int y, unsigned int size, DynamicAtlas::NodesGroup* nodes ):
        x( x ), y( y ), size( size ), nodes( nodes ), fragments( nullptr ), firstFragmentOwned( true ), owner( nullptr )
{
        ++nodes->nodesCount;
        freePixels = size * size;
}


Node::~Node()
{
        defragment();
        --nodes->nodesCount;
}


void DynamicAtlas::NodesGroup::incrementSize( unsigned int size )
{
        Node* newRoot = new Node( 0, 0, size, this );

        if ( root->isUsed() )
                newRoot->insert( root );
        else
                delete root;

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
        {
                unsigned int minLostBytes = nodesCount * sizeof( Node );
                unsigned int maxLostBytes = nodesCount * ( sizeof( Node ) + sizeof( sizeof( Node* ) ) );

                ege::engine::logger->log( ege::log::Level::WARNING,
                        "memory leak detected in nodes of texture dynamic atlas: %d nodes (%d to %d bytes)",
                        nodesCount, minLostBytes, maxLostBytes );
        }
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
        texture = new TextureRectangle( edgeThreshold, edgeThreshold );
        edgeSize = edgeThreshold;
        totalPixels = edgeThreshold * edgeThreshold;
        usedPixels = 0;
        minUnitSize = 8;
        nodes = new NodesGroup( edgeThreshold, minUnitSize );
}


void DynamicAtlas::changeEdgeSize( unsigned int size )
{
        if ( size == edgeSize )
                return;

        nodes->changeSize( size );
        texture->resize( size, size, true );
        edgeSize = size;
        totalPixels = size * size;
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
        unsigned int max = nextPowerOfTwo( width < height ? height : width );
        unsigned int leveledW = nextRepetitionOf( width, minUnitSize );
        unsigned int leveledH = nextRepetitionOf( height, minUnitSize );
        unsigned int solution[ 2 ];
        Node* root = nodes->getRoot();

        if ( !searchNLevelsDeeper( leveledW, leveledH, root, calculateStartLevel( max, max, root->size ), solution, minUnitSize ) )
        {
                unsigned int max = nextPowerOfTwo( ( width < height ) ? height : width );
                solution[ 0 ] = 0;

                if ( root->isUsed() )
                {
                        unsigned int half = max < root->size ? root->size : max;
                        changeEdgeSize( 2 * half );
                        solution[ 1 ] = half;
                }
                else
                {
                        if ( max > root->size )
                                changeEdgeSize( max );

                        solution[ 1 ] = 0;
                }
        }

        RectangularRegion* region = new RectangularRegion( *texture, solution[ 0 ], solution[ 1 ], width, height );
        nodes->getRoot()->assign( region, solution[ 0 ], solution[ 1 ], width, height );
        texture->substitute( solution[ 0 ], solution[ 1 ], imageBuffer );
        usedPixels += region->width * region->height;
        regions.insert( region );
        return region;
}


void DynamicAtlas::remove( const RectangularRegion* region )
{
        if ( regions.erase( const_cast< RectangularRegion* >( region ) ) == 0 )
                ege::exception::throwNew( "invalid argument: specified region is not contained in atlas (or no more)" );

        usedPixels -= region->width * region->height;
        nodes->getRoot()->unassign( region->x, region->y, region->width, region->height );
        delete region;

        unsigned int canBeReducedTo = nodes->canReduceSizeTo();
        canBeReducedTo = canBeReducedTo < edgeThreshold ? edgeThreshold : canBeReducedTo;
        changeEdgeSize( canBeReducedTo );
}


void DynamicAtlas::removeAll()
{
        reset();
}


const texture::TextureRectangle& DynamicAtlas::getTexture()
{
        return *texture;
}
