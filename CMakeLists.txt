CMAKE_MINIMUM_REQUIRED( VERSION 3.1 )
PROJECT( ege CXX )

INCLUDE_DIRECTORIES( include private/include )

ADD_LIBRARY( ege SHARED
        source/scenario.cxx
        source/version.cxx
        source/graphic/canvas.cxx
        source/graphic/clearer.cxx
        source/graphic/projection.cxx
        source/graphic/image.cxx
        source/graphic/painter.cxx
        source/graphic/vertices.cxx
        source/engine/configuration.cxx
        source/engine/engine.cxx
        source/resource/image.cxx
        source/resource/manager.cxx
        source/resource/resource.cxx
        source/resource/root.cxx
        )
SET_PROPERTY( TARGET ege PROPERTY CXX_STANDARD 14 )
TARGET_LINK_LIBRARIES( ege GLEW glfw )
