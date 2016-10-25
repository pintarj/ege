#include <ege/graphic/font/face.hxx>
#include <ege/engine.hxx>
#include <ege/exception.hxx>
#include <ege/graphic/gpu/texture/texture-rectangle.hxx>
#include <ege/graphic/gpu/texture/util/dynamic-atlas.hxx>
#include <ft2build.h>
#include FT_FREETYPE_H


using namespace ege::graphic::font;
using namespace ege::graphic::gpu;
using namespace ege;


class StandAloneGlyph: public Glyph
{
        public:
                StandAloneGlyph( texture::util::ImageBuffer* image, FT_GlyphSlot glyph );
                virtual ~StandAloneGlyph();
};


class AtlasGlyph: public Glyph
{
        private:
                texture::util::DynamicAtlas& atlas;

        public:
                AtlasGlyph( texture::util::ImageBuffer* image, FT_GlyphSlot glyph, texture::util::DynamicAtlas& atlas );
                virtual ~AtlasGlyph();
};


static bool initialized = false;
static FT_Library library;


struct Face::Private
{
        FT_Face face;
};


static const char* getFTErrorMessage( FT_Error error )
{
        #undef __FTERRORS_H__
        #define FT_ERRORDEF( e, v, s )  case e: return s;
        #define FT_ERROR_START_LIST     switch ( error ) {
        #define FT_ERROR_END_LIST       }
        #include FT_ERRORS_H
        return "unknown error";
}


static bool createImageFor( FT_Face face, unsigned int size, unsigned int charcode, texture::util::ImageBuffer** imageBuffer, FT_GlyphSlot* glyphSlot )
{
        FT_Set_Pixel_Sizes( face, 0, size );
        FT_UInt index = FT_Get_Char_Index( face, charcode );

        if ( index == 0 )
                return false;

        FT_Load_Glyph( face, index, 0 );
        FT_GlyphSlot glyph = face->glyph;
        *glyphSlot = face->glyph;
        FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL );
        FT_Bitmap bitmap = glyph->bitmap;

        unsigned int pixelsSize;
        unsigned char* pixels;

        if ( bitmap.rows == 0 && bitmap.width == 0 )
        {
                bitmap.rows = 1;
                bitmap.width = 1;
                pixelsSize = 4;
                pixels = new unsigned char[ pixelsSize ];
        }
        else
        {
                pixelsSize = bitmap.rows * bitmap.width * 4;
                pixels = new unsigned char[ pixelsSize ];

                for ( unsigned int y = 0; y < bitmap.rows; ++y )
                {
                        unsigned char* row = &pixels[ 4 * bitmap.width * y ];
                        unsigned char* buffer_row = &bitmap.buffer[ bitmap.width * ( bitmap.rows - y - 1 ) ];

                        for ( unsigned x = 0; x < bitmap.width; ++x )
                        {
                                unsigned offset = x << 2;

                                if ( buffer_row[ x ] == 0 )
                                {
                                        row[ offset + 0 ] = 0;
                                        row[ offset + 1 ] = 0;
                                        row[ offset + 2 ] = 0;
                                }
                                else
                                {
                                        row[ offset + 0 ] = 255;
                                        row[ offset + 1 ] = 255;
                                        row[ offset + 2 ] = 255;
                                }

                                row[ offset + 3 ] = buffer_row[ x ];
                        }
                }
        }

        using namespace buffer::usage;
        using namespace texture::util;
        std::shared_ptr< Buffer > buffer( new Buffer( pixelsSize, Frequency::STREAM, Nature::READ, pixels ) );
        delete[] pixels;
        *imageBuffer = new ImageBuffer( bitmap.width, bitmap.rows, imageBuffer::Format::RGBA, buffer );
        return true;
}


StandAloneGlyph::StandAloneGlyph( texture::util::ImageBuffer* image, FT_GlyphSlot glyph ):
        Glyph( glyph -> bitmap_left, glyph -> bitmap_top, ( float ) glyph -> advance.x / 64.0f,
               new texture::util::RectangularRegion( *new texture::TextureRectangle( *image ) ) )
{

}


StandAloneGlyph::~StandAloneGlyph()
{
        delete &region->texture;
        delete region;
}


AtlasGlyph::AtlasGlyph( texture::util::ImageBuffer* image, FT_GlyphSlot glyph, texture::util::DynamicAtlas& atlas ):
        Glyph( glyph -> bitmap_left, glyph -> bitmap_top, ( float ) glyph -> advance.x / 64.0f,
               atlas.insert( *image ) ), atlas( atlas )
{

}


AtlasGlyph::~AtlasGlyph()
{
        atlas.remove( this->region );
}


Face::Face( const char* fileName ): _private( new Face::Private )
{
        FT_Error error = 0;

        if ( !initialized )
        {
                error = FT_Init_FreeType( &library );

                if ( error )
                        Exception::throwNew( "could not initialize FreeType: %s", getFTErrorMessage( error ) );

                initialized = true;
        }

        error = FT_New_Face( library, fileName, 0, &this->_private->face );

        if ( error )
                Exception::throwNew( "could not load font face from file \"%s\": %s", fileName, getFTErrorMessage( error ) );
}


Face::~Face()
{
        FT_Done_Face( this->_private->face );
}


Glyph* Face::createGlyph( unsigned int size, unsigned int charcode )
{
        texture::util::ImageBuffer* image;
        FT_GlyphSlot glyph;

        if( !createImageFor( this->_private->face, size, charcode, &image, &glyph ) )
                return nullptr;

        StandAloneGlyph* result = new StandAloneGlyph( image, glyph );
        delete image;
        return result;
}


Glyph* Face::createGlyph( unsigned int size, unsigned int charcode, gpu::texture::util::DynamicAtlas& atlas )
{
        texture::util::ImageBuffer* image;
        FT_GlyphSlot glyph;

        if( !createImageFor( this->_private->face, size, charcode, &image, &glyph ) )
                return nullptr;

        AtlasGlyph* result = new AtlasGlyph( image, glyph, atlas );
        delete image;
        return result;
}
