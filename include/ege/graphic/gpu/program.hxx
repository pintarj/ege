

#ifndef EGE_GRAPHIC_GPU_PROGRAM_HXX
#define EGE_GRAPHIC_GPU_PROGRAM_HXX


#include <ege/graphic/gpu/object.hxx>
#include <ege/graphic/gpu/shader.hxx>
#include <initializer_list>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Program: public Object
                        {
                                public:
                                        Program( std::initializer_list< const Shader* > shaders );
                                        virtual ~Program();
                                        void use() const;
                                        int getUniformLocation( const char* uniformName ) const;
                                        void uniform( unsigned int location, int v0 );
                                        void uniformMatrix4x4( unsigned int location, unsigned int count, bool transpose, const float* matrix4x4 );
                        };
                }
        }
}


#endif
