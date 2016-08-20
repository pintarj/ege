

#ifndef EGE_PRIVATE_GRAPHIC_OPENGL_PROGRAM_HXX
#define EGE_PRIVATE_GRAPHIC_OPENGL_PROGRAM_HXX


#include <GL/glew.h>


namespace ege_private
{
        namespace graphic
        {
                namespace opengl
                {
                        namespace program
                        {
                                GLuint link( GLuint* shadersId, size_t shadersCount );

                                const char* getLastLinkLog();

                                namespace system
                                {
                                        void clearCache();
                                }
                        }
                }
        }
}


#endif
