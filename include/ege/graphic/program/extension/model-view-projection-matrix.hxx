

#ifndef EGE_GRAPHIC_PROGRAM_EXTENSION_MODEL_VIEW_PROJECTION_MATRIX_HXX
#define EGE_GRAPHIC_PROGRAM_EXTENSION_MODEL_VIEW_PROJECTION_MATRIX_HXX


#include <ege/graphic/program/extension.hxx>


namespace ege
{
        namespace graphic
        {
                namespace program
                {
                        namespace extension
                        {
                                class ModelViewProjectionMatrix: Extension
                                {
                                        private:
                                                size_t matrixLocation;

                                        protected:
                                                ModelViewProjectionMatrix( gpu::Program& program, const char* mvpMatrixName );

                                        public:
                                                void uniformMatrix( const float* matrix );
                                };
                        }
                }
        }
}


#endif
