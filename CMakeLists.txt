CMAKE_MINIMUM_REQUIRED( VERSION 3.1 )
PROJECT( ege CXX )

INCLUDE_DIRECTORIES( include )

ADD_LIBRARY( ege-core SHARED
        source/exception.cxx
        source/version.cxx
        source/engine/configuration.cxx
        source/engine/engine.cxx
        source/graphic/geometry/vertex/array.cxx
        source/graphic/geometry/vertex/buffer.cxx
        source/graphic/program/extension.cxx
        source/graphic/program/mvp-texture-program.cxx
        source/graphic/program/program.cxx
        source/graphic/program/extension/model-view-projection-matrix.cxx
        source/graphic/program/extension/textures.cxx
        source/graphic/render/draw.cxx
        source/graphic/render/targetable.cxx
        source/graphic/step/clear.cxx
        source/graphic/texture/sampler.cxx
        source/graphic/texture/texture.cxx
        source/hardware/monitor.cxx
        source/resource/root.cxx
        source/scenario/scenario.cxx
        source/util/fps/analyzer.cxx
        source/util/fps/moderator.cxx
        )
SET_PROPERTY( TARGET ege-core PROPERTY CXX_STANDARD 14 )
TARGET_LINK_LIBRARIES( ege-core GLEW glfw )
