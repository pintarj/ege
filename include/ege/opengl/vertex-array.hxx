
#ifndef EGE_OPENGL_VERTEX_ARRAY_HXX
#define EGE_OPENGL_VERTEX_ARRAY_HXX

#include <cstddef>
#include <ege/opengl/buffer.hxx>
#include <ege/opengl/object.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumeration of the attribute type.
         * */
        enum class AttributeType: unsigned int
        {
            BYTE                = 0x1400,
            DOUBLE              = 0x140A,
            FIXED               = 0x140C,
            FLOAT               = 0x1406,
            HALF_FLOAT          = 0x140B,
            INT                 = 0x1404,
            INT_2_10_10_10_REV  = 0x8D9F,
            SHORT               = 0x1402,
            UNSIGNED_BYTE       = 0x1401,
            UNSIGNED_SHORT      = 0x1403,
            UNSIGNED_INT        = 0x1405
        };

        /**
         * \brief Wrapper for the OpenGL vertex array object (AKA VAO).
         *
         * VertexArray objects are non movable and non copyable.
         * */
        class VertexArray: public Object<unsigned int>
        {
            public:
                /**
                 * \brief Create a VAO.
                 * */
                VertexArray();

                VertexArray(VertexArray&&) = delete;
                VertexArray(const VertexArray&) = delete;
                virtual ~VertexArray();

                /**
                 * \brief Bind the VAO.
                 * */
                void bind() const;

                /**
                 * \brief Enable a generic vertex attribute array.
                 * \param index Specifies the index of the generic vertex attribute to be enabled.
                 * */
                void enableAttribute(unsigned int index);

                /**
                 * \brief Disable a generic vertex attribute array.
                 * \param index Specifies the index of the generic vertex attribute to be disabled.
                 * */
                void disableAttribute(unsigned int index);

                /**
                 * \brief Bind a buffer to the vertex buffer bind point of the vertex array.
                 * \param bindingIndex The index of the vertex buffer binding point to which to bind the buffer.
                 * \param buffer The buffer to bind to the vertex buffer binding point.
                 * \param stride The distance between elements within the buffer.
                 * \param offset The offset of the first element of the buffer.
                 *
                 * Referenced OpenGL function: glVertexArrayVertexBuffer
                 * */
                void vertexBuffer(unsigned int bindingIndex, const Buffer& buffer, int stride, std::ptrdiff_t offset = 0);

                /**
                 * \brief Specify the organization of a vertex attribute array.
                 * \param index The index of generic vertex attribute array being described.
                 * \param size The number of values per vertex that are stored in the array.
                 * \param type The type of the data stored in the array.
                 * \param normalized Tells if data have to be normalized.
                 * \param relativeOffset The distance (in bytes) between elements within the buffer.
                 *
                 * Referenced OpenGL function: glVertexArrayAttribFormat
                 * */
                void attributeFormat(unsigned int attributeIndex, int size, AttributeType type, bool normalized, unsigned int relativeOffset);

                /**
                 * \brief Associate a vertex attribute and a vertex buffer binding.
                 * \param attributeIndex The vertex attribute index.
                 * \param bindingIndex The vertex buffer binding index.
                 *
                 * Referenced OpenGL function: glVertexArrayAttribBinding
                 * */
                void vertexAttributeBinding(unsigned int attributeIndex, unsigned int bindingIndex);
        };
    }
}

#endif
