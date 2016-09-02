

#ifndef EGE_HARDWARE_MONITOR_HXX
#define EGE_HARDWARE_MONITOR_HXX


#include <ege/graphic/render/targetable.hxx>


namespace ege
{
        namespace hardware
        {
                class Monitor: public graphic::render::Targetable
                {
                        private:
                                size_t width;
                                size_t height;

                        public:
                                Monitor( size_t width, size_t height );
                                void getDimensions( size_t* width, size_t* height );
                                size_t getFrameBufferId();
                };
        }
}


#endif
