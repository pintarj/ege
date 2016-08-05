

#ifndef EGE_RESOURCE_ROOT_HXX
#define EGE_RESOURCE_ROOT_HXX


#include <string>


namespace ege
{
        namespace resource
        {
                class Root
                {
                        private:
                                std::string path;

                        public:
                                Root( const std::string& path );
                                virtual ~Root();
                                const std::string& getPath();
                };
        }
}


#endif
