#include <ege/graphic/gpu/sampler.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


Sampler::Sampler()
{
        glGenSamplers( 1, &id );
        setMagFilter( sampler::Filter::LINEAR );
        setMinFilter( sampler::Filter::LINEAR );
}


Sampler::~Sampler()
{
        glDeleteSamplers( 1, &id );
}


void Sampler::setMagFilter( sampler::Filter filter )
{
        glSamplerParameteri( id, GL_TEXTURE_MAG_FILTER, ( GLenum ) filter );
}


void Sampler::setMinFilter( sampler::Filter filter )
{
        glSamplerParameteri( id, GL_TEXTURE_MIN_FILTER, ( GLenum ) filter );
}


void Sampler::bindAtUnit( unsigned int unit ) const
{
        glBindSampler( unit, id );
}
