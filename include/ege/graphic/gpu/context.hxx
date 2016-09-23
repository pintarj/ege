

#ifndef EGE_GRAPHIC_GPU_CONTEXT_HXX
#define EGE_GRAPHIC_GPU_CONTEXT_HXX


#include <ege/engine.hxx>
#include <ege/graphic/gpu/frame-buffer.hxx>
#include <ege/hardware/monitor.hxx>


namespace ege
{
        class Engine;

        namespace hardware
        {
                namespace monitor
                {
                        class VideoMode;
                }

                class Monitor;
        }

        namespace graphic
        {
                namespace gpu
                {
                        class FrameBuffer;

                        class Context
                        {
                                friend Engine;
                                friend hardware::Monitor;

                                private:
                                        FrameBuffer* defaultFrameBuffer;
                                        void* glfwContext;

                                        Context( const hardware::monitor::VideoMode& videoMode );
                                        void swapBuffers() const;

                                public:
                                        virtual ~Context();
                                        const FrameBuffer& getDefaultFrameBuffer() const;
                                        void makeCurrentOnThisThread() const;
                        };
                }
        }
}


#endif
