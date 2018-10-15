#include <ege/engine/flow.hxx>
#include <ege/engine/resources.hxx>
#include <ege/opengl/all.hxx>
#include <ege/opengl/util/matrix.hxx>

using namespace ege;

class MainScene: public flow::Scene
{
    private:
        static opengl::Program* createProgram()
        {
            static const std::string vCode =
                "#version 410\n"
                "layout(location = 0) in vec4 pVertex;"
                ""
                "uniform float minX;"
                "uniform float maxX;"
                "uniform float minY;"
                "uniform float maxY;"
                ""
                "out vec2 position;"
                ""
                "void main()"
                "{"
                "   float x0 = (pVertex.x + 1.0) / 2.0 * (maxX - minX) + minX;"
                "   float y0 = (pVertex.y + 1.0) / 2.0 * (maxY - minY) + minY;"
                "   position = vec2(x0, y0);"
                "   gl_Position = pVertex;"
                "}";

            static const std::string fCode =
                "#version 410\n"
                "precision highp float;"
                ""
                "in vec2 position;"
                ""
                "vec3 normalize_color(vec3 color)"
                "{"
                "    return color / 255.0;"
                "}"
                ""
                "vec3 map_color(int seed)"
                "{"
                "    if (seed == 0)"
                "        return vec3(255, 0, 0);"
                "    else if (seed < 16)"
                "        return vec3(16 * (16 - seed), 0, 16 * seed - 1);"
                "    else if (seed < 32)"
                "        return vec3(0, 16 * (seed - 16), 16 * (32 - seed) - 1);"
                "    else if (seed < 64)"
                "        return vec3(8 * (seed - 32), 8 * (64 - seed) - 1, 0);"
                "    else if (seed < 128)"
                "        return vec3(255 - (seed - 64) * 4, 0, 0);"
                "    else"
                "        return vec3(0, 0, 0);"
                "}"
                ""
                "void main()"
                "{"
                "    float x0 = position.x;"
                "    float y0 = position.y;"
                "    float x  = 0.0;"
                "    float y  = 0.0;"
                "    int   i  = 0;"
                ""
                "    while (true)"
                "    {"
                "        float x_pow = x * x;"
                "        float y_pow = y * y;"
                ""
                "        if (!(x_pow + y_pow < 4 && i < 128))"
                "                    break;"
                ""
                "        float tmp = x_pow - y_pow + x0;"
                "        y = 2 * x * y + y0;"
                "        x = tmp;"
                "        ++i;"
                "    }"
                ""
                "    gl_FragColor = vec4(normalize_color(map_color(i)), 1.0);"
                "}";

            auto vShader = new opengl::Shader(opengl::ShaderType::VERTEX, vCode);
            auto fShader = new opengl::Shader(opengl::ShaderType::FRAGMENT, fCode);
            auto program = new opengl::Program({vShader, fShader});
            delete vShader;
            delete fShader;
            return program;
        }

        struct Vertex
        {
            float x, y;
        };

        static opengl::Buffer* createBuffer()
        {
            static const Vertex vertices[] =
                {
                    {-1.0f, -1.0f},
                    {-1.0f, +1.0f},
                    {+1.0f, +1.0f},
                    {+1.0f, +1.0f},
                    {+1.0f, -1.0f},
                    {-1.0f, -1.0f}
                };

            return new opengl::Buffer(sizeof(vertices), opengl::BufferUsage::STATIC_DRAW, vertices);
        }

        std::unique_ptr<opengl::Program>        program;
        std::unique_ptr<opengl::Buffer>         buffer;
        std::unique_ptr<opengl::VertexArray>    vao;

        int minXLocation;
        int maxXLocation;
        int minYLocation;
        int maxYLocation;

        float minX;
        float maxX;
        float minY;
        float maxY;
        float offsetX;
        float offsetY;
        float zoom;

    public:
        MainScene():
            Scene("demo.Triangle"),
            program(createProgram()),
            buffer(createBuffer()),
            minX(-2.5f),
            maxX(+1.0f),
            minY(-1.0f),
            maxY(+1.0f),
            offsetX(0.0f),
            offsetY(0.0f),
            zoom(1.0f)
        {
            minXLocation = program->getUniformLocation("minX");
            maxXLocation = program->getUniformLocation("maxX");
            minYLocation = program->getUniformLocation("minY");
            maxYLocation = program->getUniformLocation("maxY");

            vao = std::unique_ptr<opengl::VertexArray>(new opengl::VertexArray());
            vao->vertexBuffer(0, *buffer, sizeof(Vertex));
            vao->attributeFormat(0, 2, opengl::AttributeType::FLOAT, false, 0);
            vao->vertexAttributeBinding(0, 0);
            vao->enableAttribute(0);
            program->use();
            vao->bind();
        }

        void performUpdate(const flow::Frame& frame) override
        {
            auto& keyboard = engine::getKeyboard();
            const float moveSpeed = 0.8f / zoom;
            const float zoomSpeed = 4.0f * zoom;

            if (keyboard.isPressed(keyboard::Key::UP))
                offsetY += frame.delta * moveSpeed;

            if (keyboard.isPressed(keyboard::Key::DOWN))
                offsetY -= frame.delta * moveSpeed;

            if (keyboard.isPressed(keyboard::Key::RIGHT))
                offsetX += frame.delta * moveSpeed;

            if (keyboard.isPressed(keyboard::Key::LEFT))
                offsetX -= frame.delta * moveSpeed;

            if (keyboard.isPressed(keyboard::Key::W))
                zoom += frame.delta * zoomSpeed;

            if (keyboard.isPressed(keyboard::Key::S))
                zoom -= frame.delta * zoomSpeed;

            program->uniform(minXLocation, (minX / zoom + offsetX) );
            program->uniform(maxXLocation, (maxX / zoom + offsetX) );
            program->uniform(minYLocation, (minY / zoom + offsetY) );
            program->uniform(maxYLocation, (maxY / zoom + offsetY) );
            opengl::DefaultFramebuffer& dfbo = engine::getOpenglContext().getDefaultFramebuffer();
            auto size = dfbo.getSize();
            opengl::viewport(0, 0, size.first, size.second);
            opengl::clear(opengl::FBOBuffer::COLOR);
            opengl::drawArrays(opengl::DrawMode::TRIANGLES, 0, 6);
        }
};

class Configuration: public engine::Configuration
{
    public:
        virtual const std::string getApplicationName()
        {
            return "Mandelbrot";
        }

        virtual std::shared_ptr<flow::Scene> createInitialScene()
        {
            return std::shared_ptr<flow::Scene>(new MainScene);
        }
};

int main()
{
    static Configuration configuration;
    engine::start(configuration);
    return 0;
}
