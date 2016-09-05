

#ifndef EGE_GRAPHIC_BUFFER_BUFFER_HXX
#define EGE_GRAPHIC_BUFFER_BUFFER_HXX


#include <cstddef>
#include <initializer_list>


namespace ege
{
        namespace graphic
        {
                namespace buffer
                {
                        enum class BufferUsage
                        {
                                STREAM,
                                STATIC,
                                DYNAMIC
                        };

                        enum class BufferMapAccess
                        {
                                INVALIDATE_RANGE = 0x0004,
                                UNSYNCHRONIZED = 0x0020
                        };

                        class Buffer
                        {
                                private:
                                        size_t size;
                                        size_t glBufferId;

                                public:
                                        Buffer( size_t sizeInBytes, const void* data = nullptr, BufferUsage usage = BufferUsage::STATIC );
                                        virtual ~Buffer();
                                        size_t getSize();
                                        size_t getBufferId();
                                        void* map( size_t offset, size_t length, std::initializer_list< BufferMapAccess > access = {} );
                                        void unmap();
                        };
                }
        }
}


#endif
