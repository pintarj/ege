

#ifndef EGE_GRAPHIC_IMAGE_HXX
#define EGE_GRAPHIC_IMAGE_HXX


#include <ege/graphic/image.hxx>
#include <ege/resource/image.hxx>
#include <ege/resource/manager.hxx>


namespace ege
{
        namespace graphic
        {
                class Image
                {
                        private:
                                resource::Image* res;

                        public:
                                Image( const char* idString );
                                virtual ~Image();
                };
        }
}


#endif
