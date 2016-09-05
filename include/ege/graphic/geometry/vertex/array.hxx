

#ifndef EGE_GRAPHIC_GEOMETRY_VERTEX_ARRAY_HXX
#define EGE_GRAPHIC_GEOMETRY_VERTEX_ARRAY_HXX


#include <ege/graphic/buffer/buffer.hxx>
#include <cstdint>


namespace ege
{
        namespace graphic
        {
                namespace geometry
                {
                        namespace vertex
                        {
                                struct ArrayAttribute
                                {
                                        size_t vertexIndex;
                                        uint8_t vectorSize;
                                        size_t stride;
                                        size_t offsetInBuffer;
                                        buffer::Buffer* buffer;
                                };

                                class Array
                                {
                                        private:
                                                size_t glVertexArrayId;

                                        public:
                                                Array( ArrayAttribute* attributes, size_t count );
                                                virtual ~Array();
                                                void use();
                                                size_t getVertexArrayId();
                                };
                        }
                }
        }
}


#endif
