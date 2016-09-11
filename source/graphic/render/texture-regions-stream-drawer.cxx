#include <ege/graphic/render/texture-regions-stream-drawer.hxx>
#include <ege/graphic/geometry/matrix.hxx>
#include <ege/graphic/render/draw.hxx>


using namespace ege::graphic::gpu;
using namespace ege::graphic::render;


TextureRegionsStreamDrawer::TextureRegionsStreamDrawer(): textureUnit( 0 )
{
        program = new program::MVPTextureProgram();
        mapper = new buffer::StreamMapper< Vertex >();
        gpu::Buffer* buffer = mapper->getBuffer();
        vertexArray = new gpu::VertexArray();
        vertexArray->enableAttribute( 0 );
        vertexArray->enableAttribute( 1 );
        vertexArray->setAttributeFormatAndBindVertexBuffer( 0, 3, vertexArray::attribute::Type::FLOAT, false, *buffer, offsetof( Vertex, x ), sizeof( Vertex ) );
        vertexArray->setAttributeFormatAndBindVertexBuffer( 1, 2, vertexArray::attribute::Type::FLOAT, false, *buffer, offsetof( Vertex, u ), sizeof( Vertex ) );
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
        const float xw = x + ( float ) w;
        const float yh = y + ( float ) h;

        vertex->x = x;
        vertex->y = y;
        vertex->z = 0.0f;
        vertex->u = uv[ 0 ];
        vertex->v = uv[ 1 ];
        ++vertex;

        vertex->x = x;
        vertex->y = yh;
        vertex->z = 0.0f;
        vertex->u = uv[ 2 ];
        vertex->v = uv[ 3 ];
        ++vertex;

        vertex->x = xw;
        vertex->y = y;
        vertex->z = 0.0f;
        vertex->u = uv[ 4 ];
        vertex->v = uv[ 5 ];
        ++vertex;

        vertex->x = xw;
        vertex->y = y;
        vertex->z = 0.0f;
        vertex->u = uv[ 4 ];
        vertex->v = uv[ 5 ];
        ++vertex;

        vertex->x = x;
        vertex->y = yh;
        vertex->z = 0.0f;
        vertex->u = uv[ 2 ];
        vertex->v = uv[ 3 ];
        ++vertex;

        vertex->x = xw;
        vertex->y = yh;
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
        sampler.bindAtUnit( textureUnit );
        texture->useAtUnit( textureUnit );
        vertexArray->bind();
        render::draw::arrays( render::draw::Mode::TRIANGLES, 0, unitsToDraw );
        mapper->reset();
        unitsToDraw = 0;
}
