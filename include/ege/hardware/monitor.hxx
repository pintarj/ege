

#ifndef EGE_HARDWARE_MONITOR_HXX
#define EGE_HARDWARE_MONITOR_HXX


#include <ege/graphic/gpu/context.hxx>


namespace ege
{
        class Engine;

        namespace graphic
        {
                namespace gpu
                {
                        class Context;
                }
        }

        namespace hardware
        {
                class Monitor;

                namespace monitor
                {
                        struct VideoMode
                        {
                                const unsigned int width;
                                const unsigned int height;
                                const unsigned int refreshRate;
                                const Monitor& monitor;

                                friend Monitor;

                                private:
                                        VideoMode( unsigned int width, unsigned int height, unsigned int refreshRate, const Monitor& monitor );
                        };
                }

                class Monitor
                {
                        friend Engine;
                        friend graphic::gpu::Context;

                        private:
                                graphic::gpu::Context* context;
                                monitor::VideoMode** videoModes;
                                unsigned int videoModesCount;
                                monitor::VideoMode* current;
                                void* const glfwMonitor;

                                Monitor( void* glfwMonitor );
                                void createGPUContext( const hardware::monitor::VideoMode& videoMode );
                                void createGPUContext();

                        public:
                                virtual ~Monitor();
                                const graphic::gpu::Context& getGPUContext() const;
                                const monitor::VideoMode*& getVideoModes( unsigned int* count ) const;
                                const monitor::VideoMode& getCurrentVideoMode() const;
                };
        }
}


#endif
