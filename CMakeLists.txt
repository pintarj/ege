CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(ege CXX)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(ege-core SHARED
    source/exception.cxx
    source/log.cxx
    source/version.cxx
    source/engine/configuration.cxx
    source/engine/control-thread.cxx
    source/engine/flow.cxx
    source/engine/ini-fini.cxx
    source/engine/resources.cxx
    source/flow/ege-start-scene.cxx
    source/flow/enqueue-executor.cxx
    source/flow/event-update-fragment.cxx
    source/flow/executable.cxx
    source/flow/execution-queue.cxx
    source/flow/executor.cxx
    source/flow/executor-thread.cxx
    source/flow/fps-analyzer.cxx
    source/flow/fragment.cxx
    source/flow/frame.cxx
    source/flow/origin-fragment.cxx
    source/flow/parallel-nucleus.cxx
    source/flow/scene.cxx
    source/flow/signal.cxx
    source/flow/thread.cxx
    source/glfw/keyboard.cxx
    source/glfw/monitor.cxx
    source/glfw/opengl-context.cxx
    source/glfw/opengl-default-fbo.cxx
    source/glfw/window.cxx
    source/hardware/monitor.cxx
    source/opengl/buffer.cxx
    source/opengl/blending.cxx
    source/opengl/drawing.cxx
    source/opengl/error.cxx
    source/opengl/framebuffer.cxx
    source/opengl/hint.cxx
    source/opengl/program.cxx
    source/opengl/renderbuffer.cxx
    source/opengl/shader.cxx
    source/opengl/vertex-array.cxx
    source/opengl/viewport.cxx
    )
SET_PROPERTY(TARGET ege-core PROPERTY CXX_STANDARD 14)
TARGET_LINK_LIBRARIES(ege-core GLEW glfw png freetype pthread)

ADD_EXECUTABLE(0-hello-world demo/0-hello-world.cxx)
SET_PROPERTY(TARGET 0-hello-world PROPERTY CXX_STANDARD 14)
TARGET_LINK_LIBRARIES(0-hello-world ege-core)

ADD_EXECUTABLE(1-triangle demo/1-triangle.cxx)
SET_PROPERTY(TARGET 1-triangle PROPERTY CXX_STANDARD 14)
TARGET_LINK_LIBRARIES(1-triangle ege-core)
