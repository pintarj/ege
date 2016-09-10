

#ifndef EGE_GRAPHIC_PROGRAM_MVP_TEXTURE_PROGRAM_HXX
#define EGE_GRAPHIC_PROGRAM_MVP_TEXTURE_PROGRAM_HXX


#include <ege/graphic/program/extension/textures.hxx>
#include <ege/graphic/program/extension/model-view-projection-matrix.hxx>


namespace ege
{
        namespace graphic
        {
                namespace program
                {
                        class MVPTextureProgram: public gpu::Program, public extension::Textures, public extension::ModelViewProjectionMatrix
                        {
                                public:
                                        MVPTextureProgram();
                        };
                }
        }
}


#endif
