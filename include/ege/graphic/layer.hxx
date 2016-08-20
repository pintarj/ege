

#ifndef EGE_GRAPHIC_LAYER_HXX
#define EGE_GRAPHIC_LAYER_HXX


#include <cstddef>
#include <ege/graphic/step/step.hxx>
#include <ege/graphic/geometry/projection.hxx>


namespace ege
{
        namespace graphic
        {
                struct Layer
                {
                        step::Step** steps;
                        size_t stepsNumber;
                        geometry::Projection* projection;
                };
        }
}


#endif
