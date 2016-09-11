

#ifndef EGE_GRAPHIC_GPU_VERTEX_ARRAY_HXX
#define EGE_GRAPHIC_GPU_VERTEX_ARRAY_HXX


#include <ege/graphic/gpu/object.hxx>
#include <ege/graphic/gpu/buffer.hxx>
#include <cstdint>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace vertexArray
                        {
                                namespace attribute
                                {
                                        enum class Type
                                        {
                                                BYTE = 0x1400,
                                                DOUBLE = 0x140A,
                                                FIXED = 0x140C,
                                                FLOAT = 0x1406,
                                                HALF_FLOAT = 0x140B,
                                                INT = 0x1404,
                                                INT_2_10_10_10_REV = 0x8D9F,
                                                SHORT = 0x1402,
                                                UNSIGNED_BYTE = 0x1401,
                                                UNSIGNED_SHORT = 0x1403,
                                                UNSIGNED_INT = 0x1405
                                        };
                                };
                        }

                        class VertexArray: public Object
                        {
                                public:
                                        VertexArray();
                                        virtual ~VertexArray();
                                        void enableAttribute( unsigned int index );
                                        void disableAttribute( unsigned int index );

                                        void setAttributeFormatAndBindVertexBuffer( unsigned int index, uint8_t size, vertexArray::attribute::Type type,
                                                bool normalized, const gpu::Buffer& buffer, unsigned int offset, unsigned int stride );

                                        void bind() const;
                        };
                }
        }
}


#endif
