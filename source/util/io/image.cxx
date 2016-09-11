#include <ege/util/io/image.hxx>
#include <ege/exception.hxx>
#include <cstdio>
#include <cstring>
#include <png.h>


using namespace ege::graphic::gpu;
using namespace ege::graphic::texture;
using namespace ege::util::io;


PixelsBuffer* image::loadPng( const char* fileName )
{
        std::FILE* file = std::fopen( fileName, "rb" );

        if ( file == nullptr )
                exception::throwNew( "can't open file %s", fileName );

        png_byte header[ 8 ];
        std::fread( header, 1, 8, file );

        if ( png_sig_cmp( header, 0, 8 ) )
        {
                std::fclose( file );
                exception::throwNew( "file %s is not recognized as a PNG file", fileName );
        }

        png_structp png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );

        if ( png_ptr == nullptr )
        {
                std::fclose( file );
                exception::throwNew( "error while creating png read struct for file %s", fileName );
        }

        png_infop info_ptr = png_create_info_struct( png_ptr );

        if ( info_ptr == nullptr )
        {
                png_destroy_read_struct( &png_ptr, NULL, nullptr );
                std::fclose( file );
                exception::throwNew( "error while creating png info struct for file %s", fileName );
        }

        if ( setjmp( png_jmpbuf( png_ptr ) ) )
        {
                png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
                std::fclose( file );
                exception::throwNew( "error while initializing png IO for file %s", fileName );
        }

        png_init_io( png_ptr, file );
        png_set_sig_bytes( png_ptr, 8 );
        png_read_info( png_ptr, info_ptr );
        size_t width = png_get_image_width( png_ptr, info_ptr );
        size_t height = png_get_image_height( png_ptr, info_ptr );
        png_byte color_type = png_get_color_type( png_ptr, info_ptr );
        png_get_bit_depth( png_ptr, info_ptr );
        png_set_interlace_handling( png_ptr );
        png_read_update_info( png_ptr, info_ptr );

        if ( setjmp( png_jmpbuf( png_ptr ) ) )
        {
                png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
                std::fclose( file );
                exception::throwNew( "error while reading data from png file %s", fileName );
        }

        Format format;

        switch ( color_type )
        {
                case PNG_COLOR_TYPE_RGBA:
                        format = Format::RGBA;
                        break;

                case PNG_COLOR_TYPE_RGB:
                        format = Format::RGB;
                        break;

                default:
                        png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
                        std::fclose( file );
                        exception::throwNew( "png file %s has an unsupported color type", fileName );
                        return nullptr;
        }

        const size_t rowBytes = width * format::bytesPerPixel( format );
        Buffer* pixels = new Buffer( height * rowBytes, buffer::usage::Frequency::STATIC, buffer::usage::Nature::DRAW );
        buffer::map::WriteRange* writeRange = new buffer::map::WriteRange( *pixels );
        png_bytep* rowPointers = new png_bytep[ height ];

        for ( size_t i = 0; i < height; ++i )
                rowPointers[ height - i - 1 ] = &( ( uint8_t* ) writeRange->mappedMemory )[ i * rowBytes ];

        png_read_image( png_ptr, rowPointers );
        delete rowPointers;
        png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
        std::fclose( file );
        delete writeRange;
        return new PixelsBuffer( width, height, *pixels, format, true );
}


PixelsBuffer* image::load( const char* fileName )
{
        const char* lastPoint = std::strrchr( fileName, '.' );

        if ( lastPoint == nullptr )
                exception::throwNew( "can't load image file %s, because it doesn't have an extension", fileName );

        const char* extension = lastPoint + 1;

        if ( std::strcmp( extension, "png" ) == 0 )
                return image::loadPng( fileName );

        exception::throwNew( "can't load image file %s, because the extension is not known", fileName );
        return nullptr;
}
