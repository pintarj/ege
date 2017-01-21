
#ifndef EGE_OPENGL_BUFFER_HXX
#define EGE_OPENGL_BUFFER_HXX

#include <cstddef>
#include <ege/opengl/object.hxx>

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Enumeration of buffer usage hints.
         *
         * The frequency of access may be one of these:
         *  - STREAM: The data store contents will be modified once and used at most a few times.
         *  - STATIC: The data store contents will be modified once and used many times.
         *  - DYNAMIC: The data store contents will be modified repeatedly and used many times.
         *
         * The nature of access may be one of these:
         *  - DRAW: The data store contents are modified by the application, and used as the source
         *    for GL drawing and image specification commands.
         *  - READ: The data store contents are modified by reading data from the GL, and used to
         *    return that data when queried by the application.
         *  - COPY: The data store contents are modified by reading data from the GL, and used as
         *    the source for GL drawing and image specification commands.
         * */
        enum class BufferUsage: unsigned int
        {
            STREAM_DRAW     = 0x88E0,
            STREAM_READ     = 0x88E1,
            STREAM_COPY     = 0x88E2,
            STATIC_DRAW     = 0x88E4,
            STATIC_READ     = 0x88E5,
            STATIC_COPY     = 0x88E6,
            DYNAMIC_DRAW    = 0x88E8,
            DYNAMIC_READ    = 0x88E9,
            DYNAMIC_COPY    = 0x88EA
        };

        /**
         * \brief Enumeration of buffer map access flags.
         *
         * MapAccess enums can be passed through bitwise operator.
         * */
        enum class MapAccess: unsigned int
        {
            READ                = 0x0001,
            WRITE               = 0x0002,
            PERSISTENT          = 0x0040,
            COHERENT            = 0x0080,
            INVALIDATE_BUFFER   = 0x0008,
            INVALIDATE_RANGE    = 0x0004,
            FLUSH_EXPLICIT      = 0x0010,
            UNSYNCHRONIZED      = 0x0020
        };

        /**
         * \brief Calculate the bitwise value of the two MapAccess parameters.
         * */
        static inline constexpr MapAccess operator|(MapAccess left, MapAccess right)
        {
            return (MapAccess) (static_cast<unsigned int>(left) | static_cast<unsigned int>(right));
        }

        /**
         * \brief Calculate the bitwise value of the two MapAccess parameters.
         * */
        static inline constexpr MapAccess& operator |= (MapAccess& left, MapAccess right)
        {
            left = left | right;
            return left;
        }

        /**
         * \brief Wrapper for the OpenGL buffer object.
         * \sa Buffer::allocateData()
         * \sa Buffer::mapRange()
         *
         * Buffer objects are non movable and non copyable.
         * */
        class Buffer: public Object<unsigned int>
        {
            private:
                BufferUsage usage;
                int size;

            public:
                /**
                 * \brief Creates an OpenGL buffer with no data store.
                 * */
                Buffer();

                /**
                 * \brief Creates an OpenGL buffer with an initialized data store.
                 * \param size The size in bytes of the new data store.
                 * \param usage The expected usage pattern of the data store.
                 * \param data Specifies a pointer to data that will be copied into the data store
                 *             for initialization, or \c nullptr (the default) if no data is to be copied.
                 * */
                Buffer(int size, BufferUsage usage, const void* data = nullptr);

                Buffer(Buffer&&) = delete;
                Buffer(const Buffer&) = delete;
                virtual ~Buffer();

                /**
                 * \brief Returns the size of buffer (in bytes).
                 * \return The size.
                 * */
                int getSize() const;

                /**
                 * \brief Return the usage hint given at data store creation.
                 * \return The usage, or MapUsage::STATIC_DRAW if there is no data store.
                 * */
                BufferUsage getUsage() const;

                /**
                 * \brief Creates and initializes data store.
                 * \param size The size in bytes of the new data store.
                 * \param usage The expected usage pattern of the data store.
                 * \param data Specifies a pointer to data that will be copied into the data store
                 *             for initialization, or \c nullptr (the default) if no data is to be copied.
                 *
                 * Referenced OpenGL function: glNamedBufferData
                 * */
                void allocateData(int size, BufferUsage usage, const void* data = nullptr);

                /**
                 * \brief Substitute data in \c this buffer.
                 * \param offset The offset inside \c this buffer where data will be substituted.
                 * \param size The size (in bytes) of data to be substituted.
                 * \param data The address of data to copy from RAM to VRAM.
                 *
                 * Referenced OpenGL function: glNamedBufferSubData
                 * */
                void substituteData(std::ptrdiff_t offset, int size, const void* data);

                /**
                 * \brief Copy a sub range of bytes from another buffer.
                 * \param source The other buffer.
                 * \param sourceOffset The offset inside the other buffer.
                 * \param offset The offset inside \c this buffer.
                 * \param size The size of range to copy (in bytes).
                 *
                 * Referenced OpenGL function: glCopyNamedBufferSubData
                 * */
                void copySubDataFrom(const Buffer& source, std::ptrdiff_t sourceOffset, std::ptrdiff_t offset, int size);

                /**
                 * \brief Invalidate content of the data store.
                 *
                 * Referenced OpenGL function: glInvalidateBufferData
                 * */
                void invalidateData();

                /**
                 * \brief Map all or part of data store into the client's address space.
                 * \param offset Specifies the starting offset within the buffer of the range to be mapped.
                 * \param length Specifies the length of the range to be mapped.
                 * \param access Specifies a combination of access flags indicating the desired access to the mapped range.
                 * \sa Buffer::unmap()
                 *
                 * Referenced OpenGL function: glMapNamedBufferRange
                 * */
                void* mapRange(std::ptrdiff_t offset, int length, MapAccess access);

                /**
                 * \brief Release the mapping of the data store into the client's address space.
                 * \return \c true unless the data store contents have become corrupt during the time the data
                 *         store was mapped. This can occur for system-specific reasons that affect the availability
                 *         of graphics memory, such as screen mode changes. In such situations, \c false is returned
                 *         and the data store contents are undefined. An application must detect this rare
                 *         condition and reinitialize the data store.
                 * \sa Buffer::mapRange()
                 *
                 * Referenced OpenGL function: glUnmapNamedBuffer
                 * */
                bool unmap();

                /**
                 * \brief Indicate to GPU modifications to a range of a mapped buffer.
                 * \param offset Specifies the start of the buffer subrange (in bytes).
                 * \param length Specifies the length of the buffer subrange (in bytes).
                 * \sa Buffer::mapRange()
                 *
                 * Referenced OpenGL function: glFlushMappedNamedBufferRange
                 * */
                void flushMappedRange(std::ptrdiff_t offset, int length);

                /**
                 * \brief Returns a subset of data store.
                 * \param offset Specifies the offset (in bytes) into the data store from which data will be returned.
                 * \param size Specifies the size (in bytes) of the data store region being returned.
                 * \param data Specifies a pointer to the location where buffer object data is returned.
                 * \sa Buffer::mapRange()
                 *
                 * Referenced OpenGL function: glGetNamedBufferSubData
                 * */
                void getSubData(std::ptrdiff_t offset, int size, void* data);
        };
    }
}

#endif
