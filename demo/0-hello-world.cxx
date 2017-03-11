#include <ege/engine/flow.hxx>
#include <ege/opengl/framebuffer.hxx>

using namespace ege;

class MainScene: public flow::Scene
{
    public:
        MainScene():
            flow::Scene("demo.HelloWorld")
        {

        }

        void performUpdate(const flow::Frame& frame) override
        {
            opengl::setClearColor(0.0f, 0.0f, 0.5f, 1.0f);
            opengl::clear(opengl::FBOBuffer::COLOR);
        }
};

class Configuration: public engine::Configuration
{
    public:
        virtual const std::string getApplicationName()
        {
            return "HelloWorld";
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
