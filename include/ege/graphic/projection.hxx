

#ifndef EGE_GRAPHIC_COORDINATING_SYSTEM_HXX
#define EGE_GRAPHIC_COORDINATING_SYSTEM_HXX


namespace ege
{
        namespace graphic
        {
                class Projection
                {
                        protected:
                                float matrix[ 16 ];

                                Projection( const float* matrix );

                        public:
                                const float* getMatrix();
                };
        }
}


#endif
