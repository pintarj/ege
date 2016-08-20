#include <ege/graphic/painter.hxx>
#include <ege_private/graphic/geometry/projection.hxx>
#include <GL/glew.h>


using namespace ege::graphic;
using namespace ege_private::graphic::geometry;


Painter::Painter()
{
        canvas = nullptr;
        removeLayers();
}


void Painter::setCanvas( Canvas* canvas )
{
        this->canvas = canvas;
}


void Painter::setLayers( Layer* layers, size_t count )
{
        method = [ layers, count ] ()
                {
                        for ( size_t i = 0; i < count; ++i )
                        {
                                Layer& layer = layers[ i ];
                                projection = layer.projection;

                                for ( size_t j = 0; j < layer.stepsNumber; ++j )
                                        layer.steps[ j ]->perform();
                        }
                };
}


void Painter::removeLayers()
{
        method = [] () {};
}


void Painter::paint()
{
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, canvas->getId() );
        glViewport( 0, 0, ( int ) canvas->getWidth(), ( int ) canvas->getHeight() );
        method();
}