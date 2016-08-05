CMAKE_MINIMUM_REQUIRED( VERSION 3.1 )
PROJECT( ege CXX )

INCLUDE_DIRECTORIES( include )

ADD_LIBRARY( ege SHARED
        source/engine.cxx
        source/scenario.cxx
        source/version.cxx
        source/graphic/canvas.cxx
        source/graphic/clearer.cxx
        source/graphic/painter.cxx
        source/resource/image.cxx
        source/resource/manager.cxx
        source/resource/resource.cxx
        )
SET_PROPERTY( TARGET ege PROPERTY CXX_STANDARD 14 )
TARGET_LINK_LIBRARIES( ege GLEW glfw )
