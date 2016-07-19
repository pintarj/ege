

#ifndef EGE_GRAPHIC_CANVAS_HXX
#define EGE_GRAPHIC_CANVAS_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                class Canvas
                {
                        private:
                                unsigned int glFrameBuffer;
                                unsigned int glTexture;

                        public:
                                Canvas( size_t width, size_t height );
                                virtual ~Canvas();
                                unsigned int getId();
                };
        }
}


#endif