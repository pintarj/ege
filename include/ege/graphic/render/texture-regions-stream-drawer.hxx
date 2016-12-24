

#ifndef EGE_TEXTURE_REGIONS_STREAM_DRAWER_HXX
#define EGE_TEXTURE_REGIONS_STREAM_DRAWER_HXX


#include <ege/graphic/gpu/program.hxx>
#include <ege/graphic/gpu/sampler.hxx>
#include <ege/graphic/gpu/vertex-array.hxx>
#include <ege/graphic/gpu/buffer/util/stream-write-mapper.hxx>
#include <ege/graphic/gpu/texture/util/rectangular-region.hxx>
#include <ege/math/matrix.hxx>


namespace ege
{
        namespace graphic
        {
                namespace render
                {
                        class TextureRegionsStreamDrawer
                        {
                                private:
                                        struct Vertex
                                        {
                                                float x;
                                                float y;
                                                float z;
                                                float u;
                                                float v;
                                        };

                                        const unsigned int textureUnit;
                                        gpu::Program* program;
                                        gpu::Buffer* buffer;
                                        gpu::buffer::util::StreamWriteMapper< Vertex >* mapper;
                                        gpu::VertexArray* vertexArray;
                                        const gpu::Texture* texture;
                                        gpu::Sampler sampler;
                                        unsigned int unitsToDraw;
                                        unsigned int mvpLocation;
                                        unsigned int texLocation;

                                public:
                                        TextureRegionsStreamDrawer();
                                        virtual ~TextureRegionsStreamDrawer();
                                        void setMVPMatrix( ege::math::Matrix< 4, 4, float > const& mvpMatrix );
                                        void draw( const gpu::texture::util::RectangularRegion& region, float x, float y );
                                        void flush();
                                        gpu::Sampler& getSampler();
                        };
                }
        }
}


#endif
