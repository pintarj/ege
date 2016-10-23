

#ifndef EGE_GRAPHIC_GPU_TEXTURE_UTIL_DYNAMIC_ATLAS_HXX
#define EGE_GRAPHIC_GPU_TEXTURE_UTIL_DYNAMIC_ATLAS_HXX


#include <ege/graphic/gpu/texture/texture-2D.hxx>
#include <ege/graphic/gpu/texture/util/image-buffer.hxx>
#include <ege/graphic/gpu/texture/util/rectangular-region.hxx>
#include <set>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace texture
                        {
                                namespace util
                                {
                                        class DynamicAtlas
                                        {
                                                public:
                                                        class NodesGroup;

                                                private:
                                                        Texture2D* texture;
                                                        unsigned int edgeThreshold;
                                                        unsigned int edgeSize;
                                                        unsigned int totalPixels;
                                                        unsigned int usedPixels;
                                                        unsigned int minUnitSize;
                                                        std::set< RectangularRegion* > regions;
                                                        NodesGroup* nodes;

                                                        void clear();
                                                        void reset();
                                                        void changeEdgeSize( unsigned int size );

                                                public:
                                                        DynamicAtlas( unsigned int edgeThreshold = 256 );
                                                        virtual ~DynamicAtlas();
                                                        const RectangularRegion* insert( const ImageBuffer& imageBuffer );
                                                        void remove( const RectangularRegion* region );
                                                        void removeAll();
                                                        const Texture2D& getTexture();
                                        };
                                }
                        }
                }
        }
}


#endif
