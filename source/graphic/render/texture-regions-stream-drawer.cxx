#include <ege/graphic/render/texture-regions-stream-drawer.hxx>
#include <ege/graphic/geometry/matrix.hxx>
#include <ege/graphic/gpu/draw.hxx>
#include <ege/graphic/gpu/shader.hxx>


using namespace ege::graphic::gpu;
using namespace ege::graphic::render;


static const char* ege_graphic_program_mvp_texture_program_vShader =
        "#version 400\n"
        "precision highp float;\n"
        "layout(location = 0) in vec4 vertex;\n"
        "layout(location = 1) in vec2 tex_coord;\n"
        "uniform mat4 mvp;\n"
        "out vec2 ts;\n"
        "void main(){\n"
        "    ts = tex_coord;\n"
        "    gl_Position = mvp * vertex;\n"
        "}\n"
;


static const char*  ege_graphic_program_mvp_texture_program_fShader =
        "#version 400\n"
        "precision mediump float;\n"
        "uniform sampler2DRect tex;\n"
        "in vec2 ts;\n"
        "void main(){\n"
        "    gl_FragColor = texture2DRect( tex, ts );\n"
        "}\n"
;


TextureRegionsStreamDrawer::TextureRegionsStreamDrawer(): textureUnit( 0 )
{
        Shader* vShader = new Shader( shader::Type::VERTEX, ege_graphic_program_mvp_texture_program_vShader );
        Shader* fShader = new Shader( shader::Type::FRAGMENT, ege_graphic_program_mvp_texture_program_fShader );
        program = new Program( { vShader, fShader } );
        delete vShader;
        delete fShader;
        const size_t unitsPerSector = 2048;
        const size_t sectorsCount = 2;
        buffer = new Buffer( unitsPerSector * sectorsCount * sizeof( Vertex ), buffer::usage::Frequency::STREAM, buffer::usage::Nature::DRAW );
        mapper = new buffer::util::StreamWriteMapper< Vertex >( buffer, unitsPerSector, sectorsCount );
        vertexArray = new gpu::VertexArray();
        vertexArray->enableAttribute( 0 );
        vertexArray->enableAttribute( 1 );
        vertexArray->setAttributeFormatAndBindVertexBuffer( 0, 3, vertexArray::attribute::Type::FLOAT, false, *buffer, offsetof( Vertex, x ), sizeof( Vertex ) );
        vertexArray->setAttributeFormatAndBindVertexBuffer( 1, 2, vertexArray::attribute::Type::FLOAT, false, *buffer, offsetof( Vertex, u ), sizeof( Vertex ) );
        mvpLocation = static_cast< unsigned int>( program->getUniformLocation( "mvp" ) );
        texLocation = static_cast< unsigned int>( program->getUniformLocation( "tex" ) );
        float matrix[ 16 ];
        geometry::matrix::identity( matrix );
        setMVPMatrix( matrix );
        program->uniform( texLocation, textureUnit );
        unitsToDraw = 0;
        texture = nullptr;
}


TextureRegionsStreamDrawer::~TextureRegionsStreamDrawer()
{
        delete program;
        delete mapper;
        delete vertexArray;
        delete buffer;
}


void TextureRegionsStreamDrawer::setMVPMatrix( const float* mvpMatrix )
{
        program->uniformMatrix4x4( mvpLocation, 1, false, mvpMatrix );
}


void TextureRegionsStreamDrawer::draw( const texture::util::RectangularRegion& region, float x, float y )
{
        if ( &region.texture != texture )
        {
                flush();
                texture = &region.texture;
        }

        Vertex* vertex = mapper->mapNext( 6 );

        if ( vertex == nullptr )
        {
                flush();
                vertex = mapper->mapNext( 6 );
        }

        const float* uv = region.getUVCoordinates();
        const float xw = x + ( float ) region.width;
        const float yh = y + ( float ) region.height;

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
        texture->bindAtUnit( textureUnit );
        vertexArray->bind();
        mapper->unmap();
        draw::arrays( draw::Mode::TRIANGLES, 0, unitsToDraw );
        buffer->invalidateData();
        mapper->reset();
        unitsToDraw = 0;
}
