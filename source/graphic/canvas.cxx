#include <ege/graphic/canvas.hxx>
#include <GL/glew.h>


using namespace ege::graphic;


Canvas::Canvas( size_t width, size_t height )
{
        if ( width == 0 && height == 0 )
        {
                glTexture = 0;
                glFrameBuffer = 0;
                return;
        }

        glGenTextures( 1, &glTexture );
        glBindTexture( GL_TEXTURE_2D, glTexture );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ( int ) width, ( int ) height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
        glGenFramebuffers( 1, &glFrameBuffer );
        glBindFramebuffer( GL_FRAMEBUFFER, glFrameBuffer );
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, glTexture, 0 );
}


Canvas::~Canvas()
{
        if ( glFrameBuffer == 0 )
                return;

        glDeleteFramebuffers( 1, &glFrameBuffer );
        glDeleteTextures( 1, &glTexture );
}



unsigned int Canvas::getId()
{
        return glFrameBuffer;
}
