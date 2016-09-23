

#ifndef EGE_TEXTURE_REGIONS_STREAM_DRAWER_HXX
#define EGE_TEXTURE_REGIONS_STREAM_DRAWER_HXX


#include <ege/graphic/gpu/program.hxx>
#include <ege/graphic/gpu/sampler.hxx>
#include <ege/graphic/gpu/vertex-array.hxx>
#include <ege/graphic/gpu/util/buffer/stream-write-mapper.hxx>
#include <ege/graphic/texture/rectangular-region.hxx>
#include <cstddef>


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
                                        gpu::util::buffer::StreamWriteMapper< Vertex >* mapper;
                                        gpu::VertexArray* vertexArray;
                                        gpu::Texture* texture;
                                        gpu::Sampler sampler;
                                        size_t unitsToDraw;
                                        unsigned int mvpLocation;
                                        unsigned int texLocation;

                                public:
                                        TextureRegionsStreamDrawer();
                                        virtual ~TextureRegionsStreamDrawer();
                                        void setMVPMatrix( const float* mvpMatrix );
                                        void draw( texture::RectangularRegion& region, float x, float y );
                                        void flush();
                        };
                }
        }
}


#endif
