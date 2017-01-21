#include <ege/opengl/vertex-array.hxx>
#include <GL/glew.h>

/*
 * The current implementation requires following OpenGL extensions:
 *      - GL_ARB_direct_state_access
 * */

namespace ege
{
    namespace opengl
    {
        VertexArray::VertexArray():
            Object([]() -> unsigned int
                {
                    unsigned int id;
                    glCreateVertexArrays(1, &id);
                    return id;
                }())
        {

        }

        VertexArray::~VertexArray()
        {
            glDeleteVertexArrays(1, &id);
        }

        void VertexArray::bind() const
        {
            glBindVertexArray(id);
        }

        void VertexArray::enableAttribute(unsigned int index)
        {
            glEnableVertexArrayAttrib(id, index);
        }

        void VertexArray::disableAttribute(unsigned int index)
        {
            glDisableVertexArrayAttrib(id, index);
        }

        void VertexArray::attributeFormat(unsigned int index, int size, AttributeType type, bool normalized, unsigned int relativeOffset)
        {
            glVertexArrayAttribFormat(id, index, size, (GLenum) type, (GLboolean) (normalized ? GL_TRUE : GL_FALSE), relativeOffset);
        }

        void VertexArray::vertexBuffer(unsigned int index, const Buffer& buffer, int stride, std::ptrdiff_t offset)
        {
            glVertexArrayVertexBuffer(id, index, buffer.id, offset, stride);
        }

        void VertexArray::vertexAttributeBinding(unsigned int attributeIndex, unsigned int bindingIndex)
        {
            glVertexArrayAttribBinding(id, attributeIndex, bindingIndex);
        }
    }
}