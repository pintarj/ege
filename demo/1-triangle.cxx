#include <ege/engine.hxx>
#include <ege/math/matrix.hxx>
#include <ege/opengl/all.hxx>

using namespace ege;

class MainScene: public game::Scene
{
    private:
        static opengl::Program* createProgram()
        {
            static const std::string vCode =
                "#version 410\n"
                "layout(location = 0) in vec4 pVertex;"
                "layout(location = 1) in vec4 cVertex;"
                "uniform mat4 mvp;"
                "out vec4 cTunnel;"
                "void main()"
                "{"
                "   cTunnel = cVertex;"
                "   gl_Position = mvp * pVertex;"
                "}";

            static const std::string fCode =
                "#version 410\n"
                "in vec4 cTunnel;"
                "void main()"
                "{"
                "   vec4 color = cTunnel;"
                "   gl_FragColor = color;"
                "}";

            opengl::Shader*     vShader = new opengl::Shader(opengl::ShaderType::VERTEX, vCode);
            opengl::Shader*     fShader = new opengl::Shader(opengl::ShaderType::FRAGMENT, fCode);
            opengl::Program*    program = new opengl::Program({vShader, fShader});
            delete vShader;
            delete fShader;
            return program;
        }

        struct Vertex
        {
            float x, y, r, g, b;
        };

        static opengl::Buffer* createBuffer()
        {
            static const Vertex vertices[3] =
                {
                    {0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
                    {0.866f, -0.5f, 1.0f, 0.0f, 0.0f},
                    {-0.866f, -0.5f, 0.0f, 1.0f, 0.0f}
                };

            return new opengl::Buffer(sizeof(vertices), opengl::BufferUsage::STATIC_DRAW, vertices);
        }

        std::unique_ptr<opengl::Program>        program;
        std::unique_ptr<opengl::Buffer>         buffer;
        std::unique_ptr<opengl::VertexArray>    vao;
        int                                     mvpLocation;
        float                                   radians;

    public:
        MainScene():
            program(createProgram()),
            buffer(createBuffer()),
            radians(0.0f)
        {
            vao = std::unique_ptr<opengl::VertexArray>(new opengl::VertexArray());
            vao->vertexBuffer(0, *buffer, sizeof(Vertex));
            vao->attributeFormat(0, 2, opengl::AttributeType::FLOAT, false, offsetof(Vertex, x));
            vao->attributeFormat(1, 3, opengl::AttributeType::FLOAT, false, offsetof(Vertex, r));
            vao->vertexAttributeBinding(0, 0);
            vao->vertexAttributeBinding(1, 0);
            vao->enableAttribute(0);
            vao->enableAttribute(1);
            mvpLocation = program->getUniformLocation("mvp");
            program->use();
            vao->bind();
        }

        void performUpdate(float delta)
        {
            opengl::DefaultFramebuffer& dfbo = engine::openglContext->getDefaultFramebuffer();
            auto size = dfbo.getSize();
            radians += 3.14f * delta;
            math::Matrix<4, 4> mvp = math::matrix::identity();
            mvp *= math::matrix::perspective(45.0f, ((float) size.first) / ((float) size.second), 0.01f, 100.0f);
            mvp *= math::matrix::translate(0.0f, 0.0f, -2.4f);
            mvp *= math::matrix::rotateY(radians / 6.0f);
            mvp *= math::matrix::rotateZ(radians / 2.0f);
            program->uniformMatrix4x4(mvpLocation, 1, true, &mvp[0][0]);
            opengl::viewport(0, 0, size.first, size.second);
        }

        void render()
        {
            opengl::clear(opengl::FBOBuffer::COLOR);
            opengl::drawArrays(opengl::DrawMode::TRIANGLES, 0, 3);
        }
};

class Configuration: public engine::Configuration
{
    public:
        virtual const std::string getApplicationName()
        {
            return "Triangle";
        }

        virtual std::shared_ptr<game::Scene> createInitialScene()
        {
            return std::shared_ptr<game::Scene>(new MainScene);
        }
};

int main()
{
    static Configuration configuration;
    engine::start(configuration);
    return 0;
}