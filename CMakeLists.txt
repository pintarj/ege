CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(ege CXX)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(ege-core SHARED
    source/engine.cxx
    source/exception.cxx
    source/log.cxx
    source/version.cxx
    source/game/ege-start-scene.cxx
    source/game/scene.cxx
    source/game/updateable.cxx
    source/graphic/font/face.cxx
    source/graphic/font/glyph.cxx
    source/graphic/font/library.cxx
    source/graphic/gpu/buffer.cxx
    source/graphic/gpu/context.cxx
    source/graphic/gpu/draw.cxx
    source/graphic/gpu/frame-buffer.cxx
    source/graphic/gpu/object.cxx
    source/graphic/gpu/program.cxx
    source/graphic/gpu/sampler.cxx
    source/graphic/gpu/shader.cxx
    source/graphic/gpu/texture.cxx
    source/graphic/gpu/vertex-array.cxx
    source/graphic/gpu/texture/texture-rectangle.cxx
    source/graphic/gpu/texture/texture-2D.cxx
    source/graphic/gpu/texture/two-dimensional-texture.cxx
    source/graphic/gpu/texture/util/image-buffer.cxx
    source/graphic/gpu/texture/util/dynamic-atlas.cxx
    source/graphic/gpu/texture/util/rectangular-region.cxx
    source/graphic/render/texture-regions-stream-drawer.cxx
    source/hardware/keyboard.cxx
    source/hardware/monitor.cxx
    source/opengl/program.cxx
    source/opengl/shader.cxx
    source/util/fps/analyzer.cxx
    source/util/fps/moderator.cxx
    source/util/io/image.cxx
    )
SET_PROPERTY(TARGET ege-core PROPERTY CXX_STANDARD 14)
TARGET_LINK_LIBRARIES(ege-core GLEW glfw png freetype pthread)

ADD_EXECUTABLE(0-hello-world demo/0-hello-world.cxx)
SET_PROPERTY(TARGET 0-hello-world PROPERTY CXX_STANDARD 14)
TARGET_LINK_LIBRARIES(0-hello-world ege-core)
