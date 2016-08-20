

#ifndef EGE_GRAPHIC_GEOMETRY_PROJECTION_HXX
#define EGE_GRAPHIC_GEOMETRY_PROJECTION_HXX


namespace ege
{
        namespace graphic
        {
                namespace geometry
                {
                        class Projection
                        {
                                protected:
                                        float matrix[ 16 ];

                                public:
                                        const float* getMatrix();
                        };

                        class OrthoProjection : public Projection
                        {
                                public:
                                        OrthoProjection( float left, float right, float bottom, float top, float near, float far );
                                        OrthoProjection( float left, float right, float bottom, float top );
                        };
                }
        }
}


#endif
