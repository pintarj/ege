

#ifndef EGE_RESOURCE_RESOURCE_HXX
#define EGE_RESOURCE_RESOURCE_HXX


#include <cstddef>


namespace ege
{
        namespace resource
        {
                enum class Type
                {
                        IMAGE = 0
                };

                const auto numberOfTypes = 1;

                class Resource
                {
                        private:
                                const char* idString;
                                const Type type;
                                size_t numberOfUsers;

                        protected:
                                Resource( const char* idString, Type type );

                        public:
                                virtual ~Resource();
                                const char* getIdString();
                                const Type getType();
                                void addAnUser();
                                void removeAnUser();
                                size_t getNumberOfUsers();
                };
        }
}


#endif
