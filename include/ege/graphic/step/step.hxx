

#ifndef EGE_GRAPHIC_STEP_STEP_HXX
#define EGE_GRAPHIC_STEP_STEP_HXX


namespace ege
{
        namespace graphic
        {
                namespace step
                {
                        class Step
                        {
                                public:
                                        virtual void perform() = 0;
                                        virtual ~Step() {};
                        };
                }
        }
}


#endif
