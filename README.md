# EGE ~ Entrex Game Engine

EGE is a game engine in early development. It prepares an OpenGL 4+ context
and it starts your scene.

## What it can do (at version 0.2.0)?

* automatically update/render frames on parallel threads, user should only
  create a dependencies graph between fragments (that is interesting)
* general support for parallel execution
* there are available wrappers for OpenGL API (not complete yet)
* basic support for vector and matrix operations (also graphic related operations)
* listen keyboard's key events (press/release)

## Wishlist

* complete the OpenGL API wrapper
  * add support to textures
* a resource management system
* image manipulation
  * I/O operations (PNG, JPG, BMP, ...)
  * RAM/VRAM abstraction
* fonts and glyphs
* texture atlas
* sound support

## Example of "Hello World"

That's a simple blue-screen application. Once running, press <kbd>alt</kbd>+<kbd>F4</kbd> to exit.

``` c++
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
```

## Screenshots

![wired ocean](screen/wired-ocean.png)

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
