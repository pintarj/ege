

#ifndef PRIVATE_EGE_GRAPHIC_FONT_LIBRARY_HXX
#define PRIVATE_EGE_GRAPHIC_FONT_LIBRARY_HXX


#include <ft2build.h>
#include FT_FREETYPE_H


namespace ege
{
        namespace graphic
        {
                namespace font
                {
                        namespace library
                        {
                                extern FT_Library instance;

                                const char* getErrorMessage( FT_Error error );
                                void initialize();
                                void destroy();
                        }
                }
        }
}


#endif
