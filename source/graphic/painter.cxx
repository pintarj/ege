#include <ege/graphic/painter.hxx>
#include <GL/glew.h>


using namespace ege::graphic;


Painter::Painter()
{
        canvas = nullptr;
        removeBrushStrokes();
}


void Painter::setCanvas( Canvas* canvas )
{
        this->canvas = canvas;
}


void Painter::setBrushStrokes( BrushStroke* brushStrokes, size_t count )
{
        method = [ brushStrokes, count ] ()
                {
                        for ( size_t i = 0; i < count; ++i )
                                brushStrokes[ i ].perform();
                };
}


void Painter::removeBrushStrokes()
{
        method = [] () {};
}


void Painter::paint()
{
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, canvas->getId() );
        method();
}