#include <ege/engine.hxx>
#include <ege/graphic/gpu/frame-buffer.hxx>

using namespace ege;
using namespace ege::graphic::gpu;

class MainScene: public game::Scene
{
    public:
        MainScene()
        {
            frameBuffer::setClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        }

        void performUpdate(float delta)
        {

        }

        void render()
        {
            frameBuffer::clearColorBuffer();
        }
};

int main()
{
    engine::start([](engine::Configurations& conf)
        {
            conf.createInitialScene = []()
                { return std::shared_ptr<game::Scene>(new MainScene); };
        });

    return 0;
}