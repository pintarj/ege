

#ifndef EGE_GRAPHIC_GPU_SAMPLER_HXX
#define EGE_GRAPHIC_GPU_SAMPLER_HXX


#include <cstddef>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        enum class SamplerFilter
                        {
                                NEAREST = 0x2600,
                                LINEAR = 0x2601
                        };

                        class Sampler
                        {
                                private:
                                        size_t glSamplerId;

                                public:
                                        Sampler();
                                        virtual ~Sampler();
                                        void setMagFilter( SamplerFilter filter );
                                        void setMinFilter( SamplerFilter filter );
                                        void useAtUnit( size_t unit );
                                        size_t getSamplerId();
                        };
                }
        }
}


#endif
