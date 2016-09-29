#include <ege/graphic/gpu/texture/util/dynamic-atlas.hxx>
#include <ege/exception.hxx>
#include <ege/engine.hxx>


using namespace ege;
using namespace ege::graphic::gpu;
using namespace ege::graphic::gpu::texture::util;


struct DynamicAtlas::Node
{
        unsigned int x;
        unsigned int y;
        unsigned int size;
        Node** lowers;
        RectangularRegion* owner;

        Node( unsigned int x, unsigned int y, unsigned int size );
        ~Node();
        void fragment();
        void defragment();
        inline bool isFragmented();
        inline bool isOwned();
        Node* fastSearch( unsigned int width, unsigned int height );

        inline void calculateFragmentation( unsigned int x, unsigned int y, unsigned int width, unsigned int height,
                unsigned int ( * coordinates )[ 2 ][ 4 ], bool ( * activeFragments )[ 4 ] );

        void assign( RectangularRegion* owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
        void unassign( unsigned int x, unsigned int y, unsigned int width, unsigned int height );
};


DynamicAtlas::Node::Node( unsigned int x, unsigned int y, unsigned int size )
{
        this->x = x;
        this->y = y;
        this->size = size;
        this->lowers = nullptr;
        this->owner = nullptr;
}


DynamicAtlas::Node::~Node()
{
        if ( isFragmented() )
                defragment();
}


void DynamicAtlas::Node::fragment()
{
        unsigned int half = size >> 1;
        unsigned int x0 = x;
        unsigned int y0 = y;
        unsigned int x1 = x0 + half;
        unsigned int y1 = y0 + half;

        lowers = new Node*[ 4 ];
        lowers[ 0 ] = new Node( x0, y0, half );
        lowers[ 1 ] = new Node( x0, y1, half );
        lowers[ 2 ] = new Node( x1, y0, half );
        lowers[ 3 ] = new Node( x1, y1, half );
}


inline bool DynamicAtlas::Node::isFragmented()
{
        return lowers != nullptr;
}


bool DynamicAtlas::Node::isOwned()
{
        return owner != nullptr;
}


void DynamicAtlas::Node::defragment()
{
        delete lowers[ 0 ];
        delete lowers[ 1 ];
        delete lowers[ 2 ];
        delete lowers[ 3 ];
        delete lowers;
        lowers = nullptr;
}


DynamicAtlas::Node* DynamicAtlas::Node::fastSearch( unsigned int width, unsigned int height )
{
        if ( isFragmented() )
        {
                unsigned int half = size >> 1;

                if ( width <= half && height <= half )
                {
                        for ( uint8_t i = 0; i < 4; ++i )
                        {
                                Node* result = lowers[ i ]->fastSearch( width, height );

                                if ( result != nullptr )
                                        return result;
                        }
                }
        }
        else
        {
                if ( !isOwned() )
                        return this;
        }

        return nullptr;
}


void DynamicAtlas::Node::calculateFragmentation( unsigned int x, unsigned int y, unsigned int width, unsigned int height,
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


void DynamicAtlas::Node::assign( RectangularRegion* owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
        if ( size == width && size == height )
        {
                this->owner = owner;
                return;
        }

        if ( !isFragmented() )
                fragment();

        unsigned int coordinates[ 2 ][ 4 ];
        bool activeFragments[ 4 ];
        calculateFragmentation( x, y, width, height, &coordinates, &activeFragments );

        if ( activeFragments[ 0 ] )
                lowers[ 0 ]->assign( owner, coordinates[ 0 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 0 ][ 3 ] );

        if ( activeFragments[ 1 ] )
                lowers[ 1 ]->assign( owner, coordinates[ 0 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 1 ][ 3 ] );

        if ( activeFragments[ 2 ] )
                lowers[ 2 ]->assign( owner, coordinates[ 1 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 0 ][ 3 ] );

        if ( activeFragments[ 3 ] )
                lowers[ 3 ]->assign( owner, coordinates[ 1 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 1 ][ 3 ] );
}


void DynamicAtlas::Node::unassign( unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
        if ( isFragmented() )
        {
                unsigned int coordinates[ 2 ][ 4 ];
                bool activeFragments[ 4 ];
                calculateFragmentation( x, y, width, height, &coordinates, &activeFragments );

                if ( activeFragments[ 0 ] )
                        lowers[ 0 ]->unassign( coordinates[ 0 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 0 ][ 3 ] );

                if ( activeFragments[ 1 ] )
                        lowers[ 1 ]->unassign( coordinates[ 0 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 0 ][ 2 ], coordinates[ 1 ][ 3 ] );

                if ( activeFragments[ 2 ] )
                        lowers[ 2 ]->unassign( coordinates[ 1 ][ 0 ], coordinates[ 0 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 0 ][ 3 ] );

                if ( activeFragments[ 3 ] )
                        lowers[ 3 ]->unassign( coordinates[ 1 ][ 0 ], coordinates[ 1 ][ 1 ], coordinates[ 1 ][ 2 ], coordinates[ 1 ][ 3 ] );

                if ( !lowers[ 0 ]->isFragmented() && !lowers[ 0 ]->isOwned()
                        && !lowers[ 1 ]->isFragmented() && !lowers[ 1 ]->isOwned()
                        && !lowers[ 2 ]->isFragmented() && !lowers[ 2 ]->isOwned()
                        && !lowers[ 3 ]->isFragmented() && !lowers[ 3 ]->isOwned() )
                {
                        defragment();
                }
        }
        else
        {
                owner = nullptr;
        }
}


void DynamicAtlas::clear()
{
        if ( root != nullptr )
        {
                delete root;
                root = nullptr;
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
        root = new Node( 0, 0, edgeThreshold );
}


DynamicAtlas::DynamicAtlas( unsigned int edgeThreshold )
{
        // Thanks to: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

        edgeThreshold--;
        edgeThreshold |= edgeThreshold >> 1;
        edgeThreshold |= edgeThreshold >> 2;
        edgeThreshold |= edgeThreshold >> 4;
        edgeThreshold |= edgeThreshold >> 8;
        edgeThreshold |= edgeThreshold >> 16;
        edgeThreshold++;

        static const unsigned int minimumEdgeThreshold = 32;
        this->edgeThreshold = ( edgeThreshold < minimumEdgeThreshold ) ? minimumEdgeThreshold : edgeThreshold;

        texture = nullptr;
        root = nullptr;
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

        if ( width * height + usedPixels > totalPixels )
                Exception::throwNew( "no sufficient space to insert image" );

        Node* suitable;

        if ( ( suitable = root->fastSearch( width, height ) ) == nullptr )
                Exception::throwNew( "no suitable node found to insert image" );

        RectangularRegion* region = new RectangularRegion( *texture, suitable->x, suitable->y, width, height );
        root->assign( region, suitable->x, suitable->y, width, height );
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
        root->unassign( region->x, region->y, region->width, region->height );
}


void DynamicAtlas::removeAll()
{
        reset();
}


const texture::Texture2D& DynamicAtlas::getTexture()
{
        return *texture;
}