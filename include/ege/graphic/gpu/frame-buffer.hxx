

#ifndef EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX
#define EGE_GRAPHIC_GPU_FRAME_BUFFER_HXX


#include <ege/graphic/gpu/context.hxx>
#include <ege/graphic/gpu/object.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace frameBuffer
                        {
                                void setClearColor( float r, float g, float b, float a );
                                void clearColorBuffer();
                                void clearColorBuffer( float r, float g, float b, float a );
                        }

                        class Context;

                        class FrameBuffer: public Object
                        {
                                friend Context;

                                private:
                                        unsigned int width;
                                        unsigned int height;

                                        FrameBuffer( unsigned int id );

                                public:
                                        FrameBuffer();
                                        virtual ~FrameBuffer();
                                        void bindAsDrawTarget() const;
                        };
                }
        }
}


#endif
