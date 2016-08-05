

#ifndef EGE_RESOURCE_RESOURCE_HXX
#define EGE_RESOURCE_RESOURCE_HXX


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

                        protected:
                                Resource( const char* idString, Type type );
                                virtual ~Resource();
                                const char* getIdString();
                                const Type getType();
                };
        }
}


#endif
