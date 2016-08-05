

#ifndef EGE_GRAPHIC_CANVAS_HXX
#define EGE_GRAPHIC_CANVAS_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                class Canvas
                {
                        protected:
                                size_t width;
                                size_t height;
                                unsigned int glFrameBuffer;
                                unsigned int glTexture;

                                Canvas( bool defaultCanvas, size_t width, size_t height );

                        public:
                                Canvas( size_t width, size_t height );
                                virtual ~Canvas();
                                unsigned int getId();
                                size_t getWidth();
                                size_t getHeight();
                };
        }
}


#endif