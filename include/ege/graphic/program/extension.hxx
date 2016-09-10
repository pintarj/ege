

#ifndef EGE_GRAPHIC_PROGRAM_EXTENSION_HXX
#define EGE_GRAPHIC_PROGRAM_EXTENSION_HXX


#include <ege/graphic/gpu/program.hxx>


namespace ege
{
        namespace graphic
        {
                namespace program
                {
                        class Extension
                        {
                                protected:
                                        gpu::Program& program;
                                        Extension( gpu::Program& program );
                        };
                }
        }
}


#endif
