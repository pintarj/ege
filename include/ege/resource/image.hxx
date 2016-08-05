

#ifndef EGE_RESOURCE_IMAGE_HXX
#define EGE_RESOURCE_IMAGE_HXX


#include <ege/resource/resource.hxx>


namespace ege
{
        namespace resource
        {
                class Image: public Resource
                {
                        public:
                                Image( const char* idString );
                                virtual ~Image();
                };
        }
}


#endif
