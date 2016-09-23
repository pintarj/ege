#include <ege/graphic/gpu/frame-buffer.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


static inline unsigned int createFramebuffer()
{
        unsigned int id;
        glGenFramebuffers( 1, &id );
        return id;
}


FrameBuffer::FrameBuffer( unsigned int id ): Object( id )
{

}


FrameBuffer::FrameBuffer(): FrameBuffer( createFramebuffer() )
{

}


FrameBuffer::~FrameBuffer()
{
        if ( id != 0 )
                glDeleteFramebuffers( 1, &id );
}


void FrameBuffer::bindAsDrawTarget() const
{
        glViewport( 0, 0, width, height );
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, id );
}
