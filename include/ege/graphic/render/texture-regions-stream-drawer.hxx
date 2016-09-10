

#ifndef EGE_TEXTURE_REGIONS_STREAM_DRAWER_HXX
#define EGE_TEXTURE_REGIONS_STREAM_DRAWER_HXX


#include <ege/graphic/buffer/stream-mapper.hxx>
#include <ege/graphic/gpu/vertex-array.hxx>
#include <ege/graphic/program/mvp-texture-program.hxx>
#include <ege/graphic/texture/rectangular-region.hxx>
#include <ege/graphic/gpu/sampler.hxx>


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

                                        const size_t textureUnit;
                                        program::MVPTextureProgram* program;
                                        buffer::StreamMapper< Vertex >* mapper;
                                        gpu::VertexArray* vertexArray;
                                        gpu::Texture* texture;
                                        gpu::Sampler sampler;
                                        size_t unitsToDraw;

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
