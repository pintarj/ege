

#ifndef EGE_GRAPHIC_CLEARER_HXX
#define EGE_GRAPHIC_CLEARER_HXX


#include <ege/graphic/brush-stroke.hxx>


namespace ege
{
        namespace graphic
        {
                class Clearer: public BrushStroke
                {
                        private:
                                float r, g, b, a;

                        public:
                                void setClearColor( float r, float g, float b, float a );
                                void perform();
                };
        }
}


#endif
