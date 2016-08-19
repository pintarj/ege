

#ifndef EGE_PRIVATE_OPENGL_SHADER_HXX
#define EGE_PRIVATE_OPENGL_SHADER_HXX


#include <GL/glew.h>


namespace ege_private
{
        namespace opengl
        {
                namespace shader
                {
                        GLuint compile( GLenum type, const char* source );
                        const char* getLastCompileLog();

                        namespace system
                        {
                                void clearCache();
                        }
                }
        }
}


#endif