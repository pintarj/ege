

#ifndef EGE_GRAPHIC_BRUSH_STROKE_HXX
#define EGE_GRAPHIC_BRUSH_STROKE_HXX


namespace ege
{
        namespace graphic
        {
                class BrushStroke
                {
                        public:
                                virtual void perform() = 0;
                                virtual ~BrushStroke() {};
                };
        }
}


#endif
