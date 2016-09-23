

#ifndef EGE_GRAPHIC_GPU_SHADER_HXX
#define EGE_GRAPHIC_GPU_SHADER_HXX


#include <ege/graphic/gpu/object.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace shader
                        {
                                enum class Type
                                {
                                        FRAGMENT = 0x8B30,
                                        VERTEX = 0x8B31,
                                        GEOMETRY = 0x8DD9
                                };
                        }

                        class Shader: public Object
                        {
                                public:
                                        Shader( shader::Type type, const char* sourceCode );
                                        virtual ~Shader();
                        };
                }
        }
}


#endif
