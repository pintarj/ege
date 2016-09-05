#include <ege/graphic/program/mvp-texture-program.hxx>


using namespace ege::graphic::program;


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
        "uniform sampler2D tex;\n"
        "in vec2 ts;\n"
        "void main(){\n"
        "    gl_FragColor = texture2D( tex, ts );\n"
        "}\n"
;


static const char*  ege_graphic_program_mvp_texture_program_texture = "tex";


MVPTextureProgram::MVPTextureProgram():
        Program(  ege_graphic_program_mvp_texture_program_vShader, ege_graphic_program_mvp_texture_program_fShader ),
        Textures( *this, & ege_graphic_program_mvp_texture_program_texture, 1 ),
        ModelViewProjectionMatrix( *this, "mvp" )
{

}
