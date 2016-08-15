

#ifndef EGE_GRAPHIC_RENDERER_HXX
#define EGE_GRAPHIC_RENDERER_HXX


#include <ege/graphic/canvas.hxx>
#include <ege/graphic/layer.hxx>
#include <functional>


namespace ege
{
        namespace graphic
        {
                class Painter
                {
                        private:
                                Canvas* canvas;
                                std::function< void() > method;

                        public:
                                Painter();
                                void setCanvas( Canvas* canvas );
                                void setLayers( Layer* layers, size_t count );
                                void removeLayers();
                                void paint();
                };
        }
}


#endif
