CMAKE_MINIMUM_REQUIRED( VERSION 3.1 )
PROJECT( ege CXX )

INCLUDE_DIRECTORIES( include private/include )

ADD_LIBRARY( ege SHARED
        source/scenario.cxx
        source/version.cxx
        source/graphic/canvas.cxx
        source/graphic/image.cxx
        source/graphic/painter.cxx
        source/graphic/geometry/projection.cxx
        source/graphic/geometry/transform.cxx
        source/graphic/geometry/vertex/buffer.cxx
        source/graphic/geometry/vertex/array.cxx
        source/graphic/program/program.cxx
        source/graphic/render/targetable.cxx
        source/graphic/step/clear.cxx
        source/graphic/texture/texture.cxx
        source/graphic/vertices.cxx
        source/hardware/monitor.cxx
        source/engine/configuration.cxx
        source/engine/engine.cxx
        source/resource/image.cxx
        source/resource/manager.cxx
        source/resource/resource.cxx
        source/resource/root.cxx
        private/source/graphic/geometry/projection.cxx
        private/source/graphic/opengl/program.cxx
        private/source/graphic/opengl/shader.cxx
        )
SET_PROPERTY( TARGET ege PROPERTY CXX_STANDARD 14 )
TARGET_LINK_LIBRARIES( ege GLEW glfw )
