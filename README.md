# EGE ~ Entrex Game Engine

EGE is a game engine in early development. It opens a fullscreen window,
it prepares an OpenGL 4+ context and it starts your scene.

## What it can do?

Currently (at version 0.1.2) it can't do much:

* draw in low-level using an OpenGL-like system (more or less)
* listen keyboard's key events (press/release)
* load PNG images
* load font glyphs
* insert/delete images from a texture dynamic atlas
* use GPU buffer mappers

## Example of "Hello World"

That's a simple blue-screen application. Once running, press <kbd>alt</kbd>+<kbd>F4</kbd> to exit.

``` c++
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
```

## Screenshots

![wired ocean](screen/wired-ocean.png)

## Documentation

The documentation generated by Doxygen can be found at
[http://pintarj.ddns.net/dev/ege/doc/](http://pintarj.ddns.net/dev/ege/doc/).

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

* GLFW 3
* GLEW
* PNG
* FreeType 2

In Ubuntu 16.04 (maybe also some previous versions) you can install these by typing command:

``` bash
sudo apt-get install libglfw3-dev libglew-dev libpng-dev libfreetype6-dev
```

**Have fun, Janez.**
