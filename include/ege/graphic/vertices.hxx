

#ifndef EGE_GRAPHIC_VERTICES_HXX
#define EGE_GRAPHIC_VERTICES_HXX


#include <cstdint>
#include <cstddef>


namespace ege
{
        namespace graphic
        {
                class Vertices
                {
                        private:
                                float* pointer;
                                size_t count;
                                uint8_t vectorDimension;
                                unsigned int glBuffer;

                        public:
                                Vertices();
                                ~Vertices();
                                void allocate( size_t count, uint8_t vectorDimension );
                                void deallocate();
                                float* map( size_t offset, size_t count );
                                float* mapAll();
                                void unmap();
                                uint8_t getDimension();
                                size_t getCount();
                                unsigned int getId();
                };
        }
}


#endif
