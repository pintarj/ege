#include <cmath>
#include <ege/engine/configuration.hxx>
#include <ege/engine/flow.hxx>
#include <ege/engine/resources.hxx>
#include <ege/flow/fragment.hxx>
#include <ege/opengl/all.hxx>
#include <ege/math/matrix.hxx>
#include <ege/opengl/util/matrix.hxx>

#define EDGE_SIZE       (164)
#define HALF_EDGE_SIZE  (EDGE_SIZE / 2)

using namespace ege;

static const char* vShaderCode =
    "#version 400\n"
    "precision highp float;"
    "layout(location = 0) in vec4 vertex;"
    "layout(location = 1) in vec3 colorIn;"
    "uniform mat4 mvp;"
    "out vec4 color;"
    "void main() {"
    "    float x = vertex.x;"
    "    float y = vertex.y;"
    "    float d = sqrt(x * x + y * y);"
    "    float alpha = (1.0f - d / 80.0) * (1.0 - abs(vertex.z / 60.0));"
    "    color = vec4(colorIn, alpha);"
    "    gl_Position = mvp * vertex;"
    "}";

static const char* fShaderCode =
    "#version 400\n"
    "precision mediump float;"
    "in vec4 color;"
    "void main() {"
    "    gl_FragColor = color;"
    "}";

struct Vertex
{
    math::Vector<3> xyz;
    math::Vector<3> rgb;
};

class BufferMapper: public flow::Fragment
{
    private:
        opengl::Buffer& buffer;
        Vertex* mappedArea;

    protected:
        void performUpdate(const flow::Frame& frame) override
        {
            opengl::MapAccess access = opengl::MapAccess::WRITE;
            access |= opengl::MapAccess::UNSYNCHRONIZED;
            access |= opengl::MapAccess::INVALIDATE_BUFFER;

            mappedArea = (Vertex*) buffer.mapRange(0, buffer.getSize(), access);
        }

    public:
        BufferMapper(opengl::Buffer& buffer):
            buffer(buffer)
        {

        }

        Vertex* getPointer() const noexcept
        {
            return mappedArea;
        }
};

template<unsigned Q>
class ChunkVerticesGenerator: public flow::Fragment
{
    private:
        float nodes[HALF_EDGE_SIZE + 1][HALF_EDGE_SIZE + 1];
        float phase;
        std::shared_ptr<BufferMapper> mapper;

        static inline constexpr float f(float x, float y, float t) noexcept
        {
            x /= 10.0f;
            y /= 10.0f;
            float xx = 5.0f * std::sin(t);
            float yy = 5.0f * std::cos(t);
            float point = std::sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            float hole = -1 / ((0.24f + 0.08f * std::sin(t * 4.0f)) * (x * x + y * y));
            float waveX = 4.0f * std::sin((t + x) * 1.4f) + 0.5f * std::sin((2.0f * t + x) * 4.0f);
            float waveY = 2.0f * std::sin((t + y) * 1.1f) + 0.2f * std::sin((3.0f * t + y) * 5.0f);
            float wave = waveX + waveY;
            return hole + wave + 10.0f * std::pow(2.7f, -(point * point));
        }

        void calculateNodes()
        {
            const unsigned L = HALF_EDGE_SIZE + 1;
            const int X = (Q & 0x1) ? -HALF_EDGE_SIZE : 0;
            const int Y = (Q & 0x2) ? -HALF_EDGE_SIZE : 0;

            for (int y = 0; y < L; ++y)
                for (int x = 0; x < L; ++x)
                    nodes[y][x] = f((float) (X + x), (float) (Y + y), phase);

            const unsigned index = (Q - 1) * 4 * HALF_EDGE_SIZE * HALF_EDGE_SIZE;
            Vertex* mappedArea = &mapper->getPointer()[index];

            for (int y = 0; y < L - 1; ++y)
            {
                float prev = nodes[y][0];

                for (int x = 1; x < L; ++x)
                {
                    float z = nodes[y][x];

                    mappedArea[0].xyz[0] = (float) (X + x - 1);
                    mappedArea[0].xyz[1] = (float) (Y + y);
                    mappedArea[0].xyz[2] = prev;
                    mappedArea[0].rgb[0] = 0.0f;
                    mappedArea[0].rgb[1] = 1.0f;
                    mappedArea[0].rgb[2] = 0.0f;

                    mappedArea[1].xyz[0] = (float) (X + x);
                    mappedArea[1].xyz[1] = (float) (Y + y);
                    mappedArea[1].xyz[2] = z;
                    mappedArea[1].rgb[0] = 0.0f;
                    mappedArea[1].rgb[1] = 1.0f;
                    mappedArea[1].rgb[2] = 1.0f;

                    mappedArea += 2;
                    prev = z;
                }
            }

            for (int x = 0; x < L - 1; ++x)
            {
                float prev = nodes[0][x];

                for (int y = 1; y < L; ++y)
                {
                    float z = nodes[y][x];

                    mappedArea[0].xyz[0] = (float) (X + x);
                    mappedArea[0].xyz[1] = (float) (Y + y - 1);
                    mappedArea[0].xyz[2] = prev;
                    mappedArea[0].rgb[0] = 1.0f;
                    mappedArea[0].rgb[1] = 0.0f;
                    mappedArea[0].rgb[2] = 0.0f;

                    mappedArea[1].xyz[0] = (float) (X + x);
                    mappedArea[1].xyz[1] = (float) (Y + y);
                    mappedArea[1].xyz[2] = z;
                    mappedArea[1].rgb[0] = 1.0f;
                    mappedArea[1].rgb[1] = 1.0f;
                    mappedArea[1].rgb[2] = 0.0f;

                    mappedArea += 2;
                    prev = z;
                }
            }
        }

    public:
        ChunkVerticesGenerator(std::shared_ptr<BufferMapper> mapper):
            mapper(mapper),
            phase(0.0f)
        {
            addDependency(mapper);
        }

        void performUpdate(const flow::Frame& frame) override
        {
            phase += frame.delta * 3.1415926f / 8.0f;
            calculateNodes();
        }

        bool requiresUpdateExecutionOnGraphicThread() const override
        {
            return false;
        }
};

class VerticesGenerator: public flow::Fragment
{
    private:
        opengl::Buffer& buffer;

    protected:
        void performUpdate(const flow::Frame& frame) override
        {
            buffer.unmap();
        }

    public:
        VerticesGenerator(opengl::Buffer& buffer):
            buffer(buffer)
        {
            std::shared_ptr<BufferMapper> mapper(new BufferMapper(buffer));
            addDependency(std::shared_ptr<flow::Fragment>(new ChunkVerticesGenerator<1>(mapper)));
            addDependency(std::shared_ptr<flow::Fragment>(new ChunkVerticesGenerator<2>(mapper)));
            addDependency(std::shared_ptr<flow::Fragment>(new ChunkVerticesGenerator<3>(mapper)));
            addDependency(std::shared_ptr<flow::Fragment>(new ChunkVerticesGenerator<4>(mapper)));
        }
};

class MainScene: public flow::Scene
{
    private:
        opengl::Program* program;
        opengl::Buffer* wireBuffer;
        opengl::VertexArray* wireVao;
        int mvpLocation;

    public:
        MainScene():
            flow::Scene("demo.WiredOcean"),
            wireBuffer(new opengl::Buffer(sizeof(Vertex) * 4 * EDGE_SIZE * EDGE_SIZE, opengl::BufferUsage::STREAM_DRAW))
        {
            opengl::enableLineSmooth();
            opengl::setHint(opengl::HintTarget::LINE_SMOOTH, opengl::Hint::NICEST);
            opengl::enableBlending();
            opengl::setBlendFunction(opengl::BlendFactor::SRC_ALPHA, opengl::BlendFactor::ONE_MINUS_SRC_ALPHA);
            opengl::Shader* vShader = new opengl::Shader(opengl::ShaderType::VERTEX, vShaderCode);
            opengl::Shader* fShader = new opengl::Shader(opengl::ShaderType::FRAGMENT, fShaderCode);
            program = new opengl::Program({vShader, fShader});
            delete vShader;
            delete fShader;
            mvpLocation = program->getUniformLocation("mvp");
            wireVao = new opengl::VertexArray();
            wireVao->vertexBuffer(0, *wireBuffer, sizeof(Vertex));
            wireVao->attributeFormat(0, 3, opengl::AttributeType::FLOAT, false, offsetof(Vertex, xyz));
            wireVao->attributeFormat(1, 3, opengl::AttributeType::FLOAT, false, offsetof(Vertex, rgb));
            wireVao->vertexAttributeBinding(0, 0);
            wireVao->vertexAttributeBinding(1, 0);
            wireVao->enableAttribute(0);
            wireVao->enableAttribute(1);
            addDependency(std::shared_ptr<flow::Fragment>(new VerticesGenerator(*wireBuffer)));
        }

        virtual ~MainScene()
        {
            delete wireVao;
            delete wireBuffer;
            delete program;
        }

        void performUpdate(const flow::Frame& frame) override
        {
            opengl::DefaultFramebuffer& dfbo = engine::getOpenglContext().getDefaultFramebuffer();
            auto size = dfbo.getSize();
            opengl::viewport(0, 0, size.first, size.second);
            const float factor = 1.45f;
            math::Matrix<4, 4> mvp = math::identity<4>();
            mvp *= opengl::util::perspective(3.1415926f / 4.0f, size.first / (float) size.second, 0.1f, 1000.0f);
            mvp *= opengl::util::rotateX(-3.1415926f / 3.3f);
            mvp *= opengl::util::rotateZ(-3.1415926f / 6.0f);
            mvp *= opengl::util::translate(factor * -30.0f, factor * 50.0f, factor * -32.0f);
            opengl::clear(opengl::FBOBuffer::COLOR);
            program->use();
            wireVao->bind();
            program->uniformMatrix4x4((unsigned) mvpLocation, 1, true, &mvp[0][0]);
            opengl::drawArrays(opengl::DrawMode::LINES, 0, 4 * EDGE_SIZE * EDGE_SIZE);
        }
};

class Configuration: public engine::Configuration
{
    public:
        virtual const std::string getApplicationName()
        {
            return "WiredOcean";
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
