

#ifndef EGE_GRAPHIC_GEOMETRY_TRANSFORM_HXX
#define EGE_GRAPHIC_GEOMETRY_TRANSFORM_HXX


namespace ege
{
        namespace graphic
        {
                namespace geometry
                {
                        class Transformation
                        {
                                protected:
                                        float matrix[ 16 ];
                                        bool dirty;
                                        virtual void calculate() = 0;

                                public:
                                        Transformation();
                                        const float* getMatrix();
                        };

                        class RotateTransformation: public Transformation
                        {
                                private:
                                        float radians;
                                        float vector[ 3 ];

                                public:
                                        void setAngle( float radians );
                                        void setVector( float* vector );
                                        void setVector( float x, float y, float z );

                                        void calculate();
                        };
                }
        }
}


#endif
