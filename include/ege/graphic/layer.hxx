

#ifndef EGE_GRAPHIC_LAYER_HXX
#define EGE_GRAPHIC_LAYER_HXX


#include <cstddef>
#include <ege/graphic/brush-stroke.hxx>
#include <ege/graphic/projection.hxx>


namespace ege
{
        namespace graphic
        {
                struct Layer
                {
                        BrushStroke* brushStrokes;
                        size_t numberOfBrushStrokes;
                        Projection* projection;
                };
        }
}


#endif
