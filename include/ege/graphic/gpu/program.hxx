

#ifndef EGE_GRAPHIC_GPU_PROGRAM_HXX
#define EGE_GRAPHIC_GPU_PROGRAM_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Program
                        {
                                private:
                                        const bool deleteGlProgram;

                                protected:
                                        const size_t glProgramId;
                                        Program( size_t glProgramId, bool deleteGlProgram = false );
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
