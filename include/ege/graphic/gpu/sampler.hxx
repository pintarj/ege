

#ifndef EGE_GRAPHIC_GPU_SAMPLER_HXX
#define EGE_GRAPHIC_GPU_SAMPLER_HXX


#include <ege/graphic/gpu/object.hxx>


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        namespace sampler
                        {
                                enum class Filter
                                {
                                        NEAREST = 0x2600,
                                        LINEAR = 0x2601
                                };
                        }

                        class Sampler: public Object
                        {
                                public:
                                        Sampler();
                                        virtual ~Sampler();
                                        void setMagFilter( sampler::Filter filter );
                                        void setMinFilter( sampler::Filter filter );
                                        void bindAtUnit( unsigned int unit ) const;
                        };
                }
        }
}


#endif
