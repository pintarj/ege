#include <ege/util/io/image.hxx>
#include <ege/exception.hxx>
#include <ege/graphic/gpu/buffer.hxx>
#include <cstring>
#include <memory>
#include <png.h>


using namespace ege::graphic::gpu;
using namespace ege::graphic::gpu::texture::util;
using namespace ege::util::io;


ImageBuffer* image::loadPng( const char* fileName )
{
        std::FILE* file = std::fopen( fileName, "rb" );

        if ( file == nullptr )
                Exception::throwNew( "can't open file %s", fileName );

        png_byte header[ 8 ];
        std::fread( header, 1, 8, file );

        if ( png_sig_cmp( header, 0, 8 ) )
        {
                std::fclose( file );
                Exception::throwNew( "file %s is not recognized as a PNG file", fileName );
        }

        png_structp png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );

        if ( png_ptr == nullptr )
        {
                std::fclose( file );
                Exception::throwNew( "error while creating png read struct for file %s", fileName );
        }

        png_infop info_ptr = png_create_info_struct( png_ptr );

        if ( info_ptr == nullptr )
        {
                png_destroy_read_struct( &png_ptr, NULL, nullptr );
                std::fclose( file );
                Exception::throwNew( "error while creating png info struct for file %s", fileName );
        }

        if ( setjmp( png_jmpbuf( png_ptr ) ) )
        {
                png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
                std::fclose( file );
                Exception::throwNew( "error while initializing png IO for file %s", fileName );
        }

        png_init_io( png_ptr, file );
        png_set_sig_bytes( png_ptr, 8 );
        png_read_info( png_ptr, info_ptr );
        unsigned int width = static_cast< unsigned int >( png_get_image_width( png_ptr, info_ptr ) );
        unsigned int height = static_cast< unsigned int >( png_get_image_height( png_ptr, info_ptr ) );
        png_byte color_type = png_get_color_type( png_ptr, info_ptr );
        png_get_bit_depth( png_ptr, info_ptr );
        png_set_interlace_handling( png_ptr );
        png_read_update_info( png_ptr, info_ptr );

        if ( setjmp( png_jmpbuf( png_ptr ) ) )
        {
                png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
                std::fclose( file );
                Exception::throwNew( "error while reading data from png file %s", fileName );
        }

        imageBuffer::Format format;

        switch ( color_type )
        {
                case PNG_COLOR_TYPE_RGBA:
                        format = imageBuffer::Format::RGBA;
                        break;

                case PNG_COLOR_TYPE_RGB:
                        format = imageBuffer::Format::RGB;
                        break;

                default:
                        png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
                        std::fclose( file );
                        Exception::throwNew( "png file %s has an unsupported color type", fileName );
                        return nullptr;
        }

        const unsigned int rowBytes = width * imageBuffer::format::bytesPerPixel( format );
        std::shared_ptr< Buffer > pixels( new Buffer( height * rowBytes, buffer::usage::Frequency::STATIC, buffer::usage::Nature::DRAW ) );
        buffer::map::WriteRange* writeRange = new buffer::map::WriteRange( *pixels );
        png_bytep* rowPointers = new png_bytep[ height ];

        for ( size_t i = 0; i < height; ++i )
                rowPointers[ height - i - 1 ] = &( ( uint8_t* ) writeRange->mappedMemory )[ i * rowBytes ];

        png_read_image( png_ptr, rowPointers );
        delete[] rowPointers;
        png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
        std::fclose( file );
        delete writeRange;
        return new ImageBuffer( ( unsigned int ) width, ( unsigned int ) height, format, pixels );
}


ImageBuffer* image::load( const char* fileName )
{
        const char* lastPoint = std::strrchr( fileName, '.' );

        if ( lastPoint == nullptr )
                Exception::throwNew( "can't load image file %s, because it doesn't have an extension", fileName );

        const char* extension = lastPoint + 1;

        if ( std::strcmp( extension, "png" ) == 0 )
                return image::loadPng( fileName );

        Exception::throwNew( "can't load image file %s, because the extension is not known", fileName );
        return nullptr;
}
