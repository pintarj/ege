

#ifndef EGE_GRAPHIC_GEOMETRY_VERTEX_BUFFER_HXX
#define EGE_GRAPHIC_GEOMETRY_VERTEX_BUFFER_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace geometry
                {
                        namespace vertex
                        {
                                enum class BufferUsage
                                {
                                        STREAM,
                                        STATIC,
                                        DYNAMIC
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
                                };
                        }
                }
        }
}


#endif
