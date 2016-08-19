

#ifndef EGE_GRAPHIC_VERTICES_HXX
#define EGE_GRAPHIC_VERTICES_HXX


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
                                unsigned int glBuffer;

                        public:
                                Vertices();
                                ~Vertices();
                                void allocate( size_t count );
                                void deallocate();
                                float* map( size_t offset, size_t count );
                                float* mapAll();
                                void unmap();
                                unsigned int getId();
                };
        }
}


#endif
