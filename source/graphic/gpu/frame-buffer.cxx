#include <ege/graphic/gpu/frame-buffer.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


static inline unsigned int createFramebuffer()
{
        unsigned int id;
        glGenFramebuffers( 1, &id );
        return id;
}


void frameBuffer::setClearColor( float r, float g, float b, float a )
{
        glClearColor( r, g, b, a );
}


void frameBuffer::clearColorBuffer()
{
        glClear( GL_COLOR_BUFFER_BIT );
}


void frameBuffer::clearColorBuffer( float r, float g, float b, float a )
{
        setClearColor( r, g, b, a );
        clearColorBuffer();
}


FrameBuffer::FrameBuffer( unsigned int id ): Object( id ), width( 0 ), height( 0 )
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


void FrameBuffer::attachColorBuffer( const texture::TextureRectangle& texture )
{
        glBindFramebuffer( GL_READ_FRAMEBUFFER, id );
        glFramebufferTexture2D( GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ( GLenum ) texture.type, object::getId( texture ), 0 );
        this->width = texture.getWidth();
        this->height = texture.getHeight();
}


void FrameBuffer::detachColorBuffer()
{
        glBindFramebuffer( GL_READ_FRAMEBUFFER, id );
        glFramebufferTexture2D( GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_RECTANGLE, 0, 0 );
}


void FrameBuffer::bindAsDrawTarget() const
{
        glViewport( 0, 0, width, height );
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, id );
}
