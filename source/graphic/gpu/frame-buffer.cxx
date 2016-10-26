#include <ege/graphic/gpu/frame-buffer.hxx>
#include <GL/glew.h>
#include <ege/exception.hxx>


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


FrameBuffer::FrameBuffer( unsigned int id ): Object( id ), width( 0 ), height( 0 ), colorBuffer( nullptr )
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


bool FrameBuffer::isDefault() const
{
        return id == 0;
}


void FrameBuffer::attachColorBuffer( const texture::TextureRectangle& texture )
{
        if ( isDefault() )
                Exception::throwNew( "can't attach a color buffer to the default framebuffer" );

        glBindFramebuffer( GL_READ_FRAMEBUFFER, id );
        glFramebufferTexture2D( GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ( GLenum ) texture.type, object::getId( texture ), 0 );
        this->colorBuffer = &texture;
        this->width = texture.getWidth();
        this->height = texture.getHeight();
}


void FrameBuffer::detachColorBuffer()
{
        if ( isDefault() )
                Exception::throwNew( "can't detach the color buffer from the default framebuffer" );

        glBindFramebuffer( GL_READ_FRAMEBUFFER, id );
        glFramebufferTexture2D( GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_RECTANGLE, 0, 0 );
}


unsigned int FrameBuffer::getWidth() const
{
        return width;
}


unsigned int FrameBuffer::getHeight() const
{
        return height;
}


void FrameBuffer::bindAsDrawTarget() const
{
        glViewport( 0, 0, width, height );
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, id );
}


void FrameBuffer::blit( const FrameBuffer& destination, const FrameBuffer& source,
        unsigned int dstX0, unsigned int dstY0, unsigned int dstX1, unsigned int dstY1,
        unsigned int srcX0, unsigned int srcY0, unsigned int srcX1, unsigned int srcY1,
        sampler::Filter filter )
{
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, object::getId( destination ) );
        glBindFramebuffer( GL_READ_FRAMEBUFFER, object::getId( source ) );
        glBlitFramebuffer( srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, GL_COLOR_BUFFER_BIT, ( GLenum ) filter );
}
