#include <ege/graphic/gpu/sampler.hxx>
#include <GL/glew.h>


using namespace ege::graphic::gpu;


static inline unsigned int generateSampler()
{
        unsigned int id;
        glGenSamplers( 1, &id );
        return id;
}


Sampler::Sampler(): Object( generateSampler() )
{
        setMagFilter( sampler::Filter::LINEAR );
        setMinFilter( sampler::Filter::LINEAR );
        glSamplerParameteri( id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glSamplerParameteri( id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
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
