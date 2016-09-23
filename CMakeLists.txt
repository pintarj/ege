CMAKE_MINIMUM_REQUIRED( VERSION 3.1 )
PROJECT( ege CXX )

INCLUDE_DIRECTORIES( include )

ADD_LIBRARY( ege-core SHARED
        source/exception.cxx
        source/version.cxx
        source/engine.cxx
        source/game/scene.cxx
        source/graphic/gpu/buffer.cxx
        source/graphic/gpu/context.cxx
        source/graphic/gpu/draw.cxx
        source/graphic/gpu/frame-buffer.cxx
        source/graphic/gpu/object.cxx
        source/graphic/gpu/program.cxx
        source/graphic/gpu/sampler.cxx
        source/graphic/gpu/shader.cxx
        source/graphic/gpu/texture.cxx
        source/graphic/gpu/texture-2D.cxx
        source/graphic/gpu/vertex-array.cxx
        source/graphic/gpu/util/image/buffer.cxx
        source/graphic/render/texture-regions-stream-drawer.cxx
        source/graphic/step/clear.cxx
        source/graphic/texture/rectangular-region.cxx
        source/graphic/texture/region.cxx
        source/hardware/monitor.cxx
        source/util/fps/analyzer.cxx
        source/util/fps/moderator.cxx
        source/util/io/image.cxx
        )
SET_PROPERTY( TARGET ege-core PROPERTY CXX_STANDARD 14 )
TARGET_LINK_LIBRARIES( ege-core GLEW glfw png )
