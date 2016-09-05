

#ifndef EGE_GRAPHIC_PROGRAM_PROGRAM_HXX
#define EGE_GRAPHIC_PROGRAM_PROGRAM_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace program
                {
                        class Program
                        {
                                protected:
                                        const size_t glProgramId;
                                        Program( size_t glProgramId );
                                        Program( const char* vertexShader, const char* fragmentShader );

                                public:
                                        virtual ~Program();
                                        void use();
                                        const size_t getProgramId();
                        };
                }
        }
}


#endif
