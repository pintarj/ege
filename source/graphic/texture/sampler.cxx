#include <ege/graphic/texture/sampler.hxx>
#include <GL/glew.h>


using namespace ege::graphic::texture;


Sampler::Sampler()
{
        GLuint id;
        glGenSamplers( 1, &id );
        glSamplerParameteri( id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glSamplerParameteri( id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glSamplerId = id;
        setMagFilter( SamplerFilter::LINEAR );
        setMinFilter( SamplerFilter::LINEAR );
}


Sampler::~Sampler()
{
        GLuint id = ( GLuint ) glSamplerId;
        glDeleteSamplers( 1, &id );
}


void Sampler::setMagFilter( SamplerFilter filter )
{
        glSamplerParameteri( ( GLuint ) glSamplerId, GL_TEXTURE_MAG_FILTER, ( GLenum ) filter );
}


void Sampler::setMinFilter( SamplerFilter filter )
{
        glSamplerParameteri( ( GLuint ) glSamplerId, GL_TEXTURE_MIN_FILTER, ( GLenum ) filter );
}


size_t Sampler::getSamplerId()
{
        return glSamplerId;
}