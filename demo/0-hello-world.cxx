#include <ege/engine.hxx>
#include <ege/opengl/framebuffer.hxx>

using namespace ege;

class MainScene: public flow::Scene
{
    public:
        MainScene()
        {
            opengl::setClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        }

        void performUpdate(float delta)
        {

        }

        void render()
        {
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
