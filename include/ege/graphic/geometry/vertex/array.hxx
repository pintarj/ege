

#ifndef EGE_GRAPHIC_GEOMETRY_VERTEX_CONNECTOR_HXX
#define EGE_GRAPHIC_GEOMETRY_VERTEX_CONNECTOR_HXX


#include <ege/graphic/geometry/vertex/buffer.hxx>
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
                                        Buffer* buffer;
                                };

                                class Array
                                {
                                        private:
                                                size_t glVertexArrayId;

                                        public:
                                                Array( ArrayAttribute* attributes, size_t count );
                                                void use();
                                                size_t getVertexArrayId();
                                };
                        }
                }
        }
}


#endif
