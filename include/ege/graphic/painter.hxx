

#ifndef EGE_GRAPHIC_RENDERER_HXX
#define EGE_GRAPHIC_RENDERER_HXX


#include <ege/graphic/canvas.hxx>
#include <ege/graphic/brush-stroke.hxx>
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
                                void setBrushStrokes( BrushStroke* brushStrokes, size_t count );
                                void removeBrushStrokes();
                                void paint();
                };
        }
}


#endif
