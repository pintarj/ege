#include <ege/graphic/gpu/object.hxx>


using namespace ege::graphic::gpu;


unsigned int object::getId( const Object &object )
{
        return object.id;
}


Object::Object( unsigned int id ): id( id )
{

}