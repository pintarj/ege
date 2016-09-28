# EGE ~ Entrex Game Engine

EGE is a game engine in early development. It opens a fullscreen window,
it prepares an OpenGL 4+ context and it starts your scene.


## What it can do?

Currently (at version 0.1.1) it can't do much:

* draw in low-level using an OpenGL-like system (more or less)
* listen keyboard's key events (press/release)
* load PNG images
* insert/delete images from a texture dynamic atlas
* use GPU buffer mappers


## Example of "Hello World"

That's a simple blue-screen application. Once running, press <kbd>alt</kbd>+<kbd>F4</kbd> to exit.

``` c++
#include <ege/engine.hxx>
#include <ege/graphic/gpu/frame-buffer.hxx>


using namespace ege;
using namespace ege::graphic::gpu;


class MainScene: public game::Scene
{
        public:
                MainScene()
                {
                        frameBuffer::setClearColor( 0.0f, 0.0f, 0.5f, 1.0f );
                }

                void update( float delta )
                {

                }

                void render()
                {
                        frameBuffer::clearColorBuffer();
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


## Build library

The project uses CMake as build system. To build the library perform those commands
in the project's root folder:

``` bash
mkdir build
cd build
cmake ..
make
```


### Dependencies

EGE depend on some third-party libraries:

* glfw3
* glew
* png

In Ubuntu 16.04 (maybe also some previous versions) you can install these by typing command:

``` bash
sudo apt-get install libglfw3-dev libglew-dev libpng-dev
```

**Have fun, Janez.**
