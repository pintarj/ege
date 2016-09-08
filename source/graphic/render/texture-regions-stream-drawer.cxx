#include <ege/graphic/render/texture-regions-stream-drawer.hxx>
#include <ege/graphic/geometry/matrix.hxx>
#include <ege/graphic/render/draw.hxx>


using namespace ege::graphic::render;


TextureRegionsStreamDrawer::TextureRegionsStreamDrawer(): textureUnit( 0 )
{
        program = new program::MVPTextureProgram();
        mapper = new buffer::StreamMapper< Vertex >();
        buffer::Buffer* buffer = mapper->getBuffer();

        geometry::vertex::ArrayAttribute attributes[ 2 ] =
                {
                        { 0, 3, sizeof( Vertex ), ( size_t ) &( ( Vertex* ) 0 )->x, buffer },
                        { 1, 2, sizeof( Vertex ), ( size_t ) &( ( Vertex* ) 0 )->u, buffer }
                };

        vertexArray = new geometry::vertex::Array( &attributes[ 0 ], 2 );
        float matrix[ 16 ];
        geometry::matrix::identity( matrix );
        program->uniformMatrix( matrix );
        program->uniformTextureAt( 0, textureUnit );
        unitsToDraw = 0;
        texture = nullptr;
}


TextureRegionsStreamDrawer::~TextureRegionsStreamDrawer()
{
        delete program;
        delete mapper;
        delete vertexArray;
}


void TextureRegionsStreamDrawer::setMVPMatrix( const float* mvpMatrix )
{
        program->uniformMatrix( mvpMatrix );
}


void TextureRegionsStreamDrawer::draw( texture::RectangularRegion& region, float x, float y )
{
        if ( &region.getTexture() != texture )
        {
                flush();
                texture = &region.getTexture();
        }

        Vertex* vertex = mapper->mapNext( 6 );

        if ( vertex == nullptr )
        {
                flush();
                vertex = mapper->mapNext( 6 );
        }

        size_t w, h;
        region.getDimensions( &w, &h );
        const float* uv = region.getUVCoordinates();
        const float rtx = x + ( float ) w;
        const float rty = y + ( float ) h;

        vertex->x = x;
        vertex->y = y + ( float ) h;
        vertex->z = 0.0f;
        vertex->u = uv[ 0 ];
        vertex->v = uv[ 1 ];
        ++vertex;

        vertex->x = x;
        vertex->y = y;
        vertex->z = 0.0f;
        vertex->u = uv[ 2 ];
        vertex->v = uv[ 3 ];
        ++vertex;

        vertex->x = rtx;
        vertex->y = rty;
        vertex->z = 0.0f;
        vertex->u = uv[ 4 ];
        vertex->v = uv[ 5 ];
        ++vertex;

        vertex->x = rtx;
        vertex->y = rty;
        vertex->z = 0.0f;
        vertex->u = uv[ 4 ];
        vertex->v = uv[ 5 ];
        ++vertex;

        vertex->x = x;
        vertex->y = y;
        vertex->z = 0.0f;
        vertex->u = uv[ 2 ];
        vertex->v = uv[ 3 ];
        ++vertex;

        vertex->x = x + ( float ) w;
        vertex->y = y;
        vertex->z = 0.0f;
        vertex->u = uv[ 6 ];
        vertex->v = uv[ 7 ];

        unitsToDraw += 6;
}


void TextureRegionsStreamDrawer::flush()
{
        if ( unitsToDraw == 0 )
                return;

        program->use();
        sampler.useAtUnit( textureUnit );
        texture->useAtUnit( textureUnit );
        vertexArray->use();
        render::draw::arrays( render::draw::Mode::TRIANGLES, 0, unitsToDraw );
        mapper->reset();
        unitsToDraw = 0;
}
