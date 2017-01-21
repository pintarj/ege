#include <ege/opengl/buffer.hxx>
#include <GL/glew.h>

/*
 * The current implementation requires following OpenGL extensions:
 *      - GL_ARB_direct_state_access
 *      - GL_ARB_invalidate_subdata
 * */

namespace ege
{
    namespace opengl
    {
        Buffer::Buffer():
            Object([]() -> unsigned int
                {
                    unsigned int id;
                    glCreateBuffers(1, &id);
                    return id;
                }()),
            size(0),
            usage(BufferUsage::STATIC_DRAW)
        {

        }

        Buffer::Buffer(int size, BufferUsage usage, const void* data):
            Buffer()
        {
            allocateData(size, usage, data);
        }

        Buffer::~Buffer()
        {
            glDeleteBuffers(1, &id);
        }

        int Buffer::getSize() const
        {
            return size;
        }

        BufferUsage Buffer::getUsage() const
        {
            return usage;
        }

        void Buffer::allocateData(int size, BufferUsage usage, const void* data)
        {
            glNamedBufferData(id, size, data, static_cast<unsigned int>(usage));
            this->size  = size;
            this->usage = usage;
        }

        void Buffer::substituteData(std::ptrdiff_t offset, int size, const void* data)
        {
            glNamedBufferSubData(id, offset, size, data);
        }

        void Buffer::copySubDataFrom(const Buffer& source, std::ptrdiff_t sourceOffset, std::ptrdiff_t offset, int size)
        {
            glCopyNamedBufferSubData(source.id, id, sourceOffset, offset, size);
        }

        void Buffer::invalidateData()
        {
            glInvalidateBufferData(id);
        }

        void* Buffer::mapRange(std::ptrdiff_t offset, int length, MapAccess access)
        {
            unsigned int rawAccess = static_cast<unsigned int>(access);
            void* mappedMemory = glMapNamedBufferRange(id, offset, length, rawAccess);
            return mappedMemory;
        }

        bool Buffer::unmap()
        {
            bool allRight = glUnmapNamedBuffer(id) == GL_TRUE;
            return allRight;
        }

        void Buffer::flushMappedRange(std::ptrdiff_t offset, int length)
        {
            glFlushMappedNamedBufferRange(id, offset, length);
        }

        void Buffer::getSubData(std::ptrdiff_t offset, int size, void* data)
        {
            glGetNamedBufferSubData(id, offset, size, data);
        }
    }
}
