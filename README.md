# EGE ~ Entrex Game Engine

EGE is a game engine in early development. It opens a fullscreen window,
it prepares an OpenGL 4+ context and it starts your scene.


### What it can do?

Currently (at version 0.1.1) it can't do much:

* draw in low-level using an OpenGL-like system (more or less)
* load PNG images
* use GPU buffer mappers


### Example of "Hello World"

Press <kbd>alt</kbd>+<kbd>F4</kbd> to exit.

``` c++
#include <ege/engine.hxx>

using namespace ege;

class MainScene: public game::Scene
{
    public:
        void update( float delta )
        {

        }

        void render()
        {

        }
};

int main()
{
    engine::start( [] ( engine::Configurations& conf )
        {
            conf.createInitialScene = [] () { return new MainScene; };
        } );

    return 0;
}
```

**Have fun, Janez.**
