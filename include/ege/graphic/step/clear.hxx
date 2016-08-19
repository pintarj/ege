

#ifndef EGE_GRAPHIC_STEP_CLEAR_HXX
#define EGE_GRAPHIC_STEP_CLEAR_HXX


#include <ege/graphic/step/step.hxx>


namespace ege
{
        namespace graphic
        {
                namespace step
                {
                        class Clear : public step::Step
                        {
                                private:
                                        float r, g, b, a;

                                public:
                                        void setClearColor( float r, float g, float b, float a );

                                        void perform();
                        };
                }
        }
}


#endif
