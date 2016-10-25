#include <ege/graphic/font/face.hxx>
#include <ege/engine.hxx>
#include <ege/exception.hxx>
#include <ege/graphic/gpu/texture/texture-rectangle.hxx>
#include <ft2build.h>
#include FT_FREETYPE_H


using namespace ege::graphic::font;
using namespace ege;


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
        FT_Set_Pixel_Sizes( this->_private->face, 0, size );
        FT_UInt index = FT_Get_Char_Index( this->_private->face, charcode );

        if ( index == 0 )
                return nullptr;

        FT_Load_Glyph( this->_private->face, index, 0 );
        FT_GlyphSlot glyph = this->_private->face->glyph;
        FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL );
        FT_Bitmap bitmap = glyph->bitmap;

        unsigned int pixelsSize = bitmap.rows * bitmap.width * 4;
        unsigned char* pixels = new unsigned char[ pixelsSize ];

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

        std::shared_ptr< gpu::Buffer > buffer( new gpu::Buffer( pixelsSize, gpu::buffer::usage::Frequency::STREAM, gpu::buffer::usage::Nature::READ, pixels ) );
        delete pixels;
        gpu::texture::util::ImageBuffer* image = new gpu::texture::util::ImageBuffer( bitmap.width, bitmap.rows, gpu::texture::util::imageBuffer::Format::RGBA, buffer );
        gpu::texture::TextureRectangle* texture = new gpu::texture::TextureRectangle( *image );
        delete image;
        gpu::texture::util::RectangularRegion* region = new gpu::texture::util::RectangularRegion( *texture );
        return new Glyph( glyph -> bitmap_left, glyph -> bitmap_top, ( float ) glyph -> advance.x / 64.0f, region, true );
}
