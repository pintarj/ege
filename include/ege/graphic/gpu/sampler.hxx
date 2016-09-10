

#ifndef EGE_GRAPHIC_GPU_SAMPLER_HXX
#define EGE_GRAPHIC_GPU_SAMPLER_HXX


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

                        class Sampler
                        {
                                private:
                                        unsigned int id;

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
