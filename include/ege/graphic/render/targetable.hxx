

#ifndef EGE_GRAPHIC_RENDER_TARGETABLE_HXX
#define EGE_GRAPHIC_RENDER_TARGETABLE_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace render
                {
                        class Targetable
                        {
                                public:
                                        virtual void getDimensions( size_t* width, size_t* height ) = 0;
                                        virtual size_t getFrameBufferId() = 0;
                                        virtual void setAsTarget();
                                        virtual ~Targetable() {};
                        };
                }
        }
}


#endif
