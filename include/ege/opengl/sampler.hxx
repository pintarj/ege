
#ifndef EGE_OPENGL_SAMPLER_HXX
#define EGE_OPENGL_SAMPLER_HXX

namespace ege
{
    namespace opengl
    {
        enum class Filter: unsigned int
        {
            NEAREST = 0x2600,
            LINEAR  = 0x2601
        };
    }
}

#endif
