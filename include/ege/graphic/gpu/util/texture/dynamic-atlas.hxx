

#ifndef EGE_GRAPHIC_GPU_UTIL_TEXTURE_DYNAMIC_ATLAS_HXX
#define EGE_GRAPHIC_GPU_UTIL_TEXTURE_DYNAMIC_ATLAS_HXX


#include <ege/graphic/gpu/texture-2D.hxx>
#include <ege/graphic/gpu/util/image/buffer.hxx>
#include <ege/graphic/gpu/util/texture/rectangular-region.hxx>
#include <set>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace util
                        {
                                namespace texture
                                {
                                        class DynamicAtlas
                                        {
                                                private:
                                                        struct Node;

                                                        Texture2D* texture;
                                                        unsigned int edgeThreshold;
                                                        unsigned int edgeSize;
                                                        unsigned int totalPixels;
                                                        unsigned int usedPixels;
                                                        std::set< RectangularRegion* > regions;
                                                        Node* root;

                                                        void clear();
                                                        void reset();

                                                public:
                                                        DynamicAtlas( unsigned int edgeThreshold = 256 );
                                                        virtual ~DynamicAtlas();
                                                        const RectangularRegion* insert( const image::Buffer& imageBuffer );
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
