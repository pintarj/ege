

#ifndef EGE_GRAPHIC_GPU_OBJECT_HXX
#define EGE_GRAPHIC_GPU_OBJECT_HXX


namespace ege
{
        namespace graphic
        {
                namespace gpu
                {
                        class Object;
                        class VertexArray;

                        namespace object
                        {
                                unsigned int getId( const Object& object );
                        }

                        class Object
                        {
                                friend VertexArray;
                                friend unsigned int object::getId( const Object &object );

                                protected:
                                        const unsigned int id;

                                        Object( unsigned int id );
                                        virtual ~Object();
                        };
                }
        }
}


#endif
