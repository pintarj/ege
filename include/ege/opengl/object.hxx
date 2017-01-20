
#ifndef EGE_OPENGL_OBJECT_HXX
#define EGE_OPENGL_OBJECT_HXX

namespace ege
{
    namespace opengl
    {
        /**
         * \brief Represent the base class for any OpenGL object class.
         *
         * Classes that extends this one represent an OpenGL object in GPU
         * (buffer, shader, texture, ...). \n
         * Objects are non movable or copyable.
         *
         * \param T The type of the object's id.
         * */
        template <typename T = unsigned int>
        class Object
        {
            protected:
                /**
                 * \brief Stores the id.
                 * \param id The stored id.
                 * */
                Object(const T& id): id(id) {}

            public:
                /**
                 * \brief The id of the object.
                 * */
                const T id;

                Object(Object&&) = delete;
                Object(const Object&) = delete;
                virtual ~Object() {}
        };
    }
}

#endif
