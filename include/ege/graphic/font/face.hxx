

#ifndef EGE_GRAPHIC_FONT_FACE_HXX
#define EGE_GRAPHIC_FONT_FACE_HXX


#include <ege/graphic/font/glyph.hxx>
#include <memory>


namespace ege
{
        namespace graphic
        {
                namespace font
                {
                        class Glyph;

                        class Face
                        {
                                private:
                                        struct Private;
                                        std::unique_ptr< Private > _private;

                                public:
                                        Face( const char* fileName );
                                        virtual ~Face();
                                        Glyph* createGlyph( unsigned int size, unsigned int charcode );
                        };
                }
        }
}


#endif
