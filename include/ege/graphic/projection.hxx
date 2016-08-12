

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

                class OrthoProjection: public Projection
                {
                        public:
                                OrthoProjection( float left, float right, float bottom, float top, float near, float far );
                                OrthoProjection( float left, float right, float bottom, float top );
                };
        }
}


#endif
