

#ifndef EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX
#define EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX


#include <ege/engine.hxx>
#include <ege/graphic/gpu/object.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class FrameBuffer: public Object
                        {
                                friend Engine;

                                private:
                                        FrameBuffer( unsigned int id );

                                public:
                                        FrameBuffer();
                                        virtual ~FrameBuffer();
                        };
                }
        }
}


#endif
