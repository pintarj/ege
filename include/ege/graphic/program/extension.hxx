

#ifndef EGE_GRAPHIC_PROGRAM_EXTENSION_HXX
#define EGE_GRAPHIC_PROGRAM_EXTENSION_HXX


#include <ege/graphic/program/program.hxx>


namespace ege
{
        namespace graphic
        {
                namespace program
                {
                        class Extension
                        {
                                protected:
                                        Program& program;
                                        Extension( Program& program );
                        };
                }
        }
}


#endif
