

#ifndef EGE_GRAPHIC_GPU_VERTEX_ARRAY_HXX
#define EGE_GRAPHIC_GPU_VERTEX_ARRAY_HXX


#include <ege/graphic/gpu/buffer.hxx>
#include <cstddef>
#include <cstdint>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace vertexArray
                        {
                                struct Attribute
                                {
                                        size_t vertexIndex;
                                        uint8_t vectorSize;
                                        size_t stride;
                                        size_t offsetInBuffer;
                                        gpu::Buffer* buffer;
                                };
                        }

                        class VertexArray
                        {
                                private:
                                        size_t glVertexArrayId;

                                public:
                                        VertexArray( vertexArray::Attribute* attributes, size_t count );
                                        virtual ~VertexArray();
                                        void use();
                                        size_t getVertexArrayId();
                        };
                }
        }
}


#endif
