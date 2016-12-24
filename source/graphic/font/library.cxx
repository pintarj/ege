#include <private/ege/graphic/font/library.hxx>
#include <ege/exception.hxx>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <atomic>
#include <ege/engine.hxx>


static std::atomic_bool initialized( false );
FT_Library ege::graphic::font::library::instance;


const char* ege::graphic::font::library::getErrorMessage( FT_Error error )
{
        #undef __FTERRORS_H__
        #define FT_ERRORDEF( e, v, s )  case e: return s;
        #define FT_ERROR_START_LIST     switch ( error ) {
        #define FT_ERROR_END_LIST       }
        #include FT_ERRORS_H
        return "unknown error";
}


void ege::graphic::font::library::initialize()
{
        if ( initialized.exchange( true ) )
                ege::exception::throwNew( "FreeType library was already initialized" );

        FT_Error error = FT_Init_FreeType( &ege::graphic::font::library::instance );

        if ( error )
                ege::exception::throwNew( "could not initialize FreeType: %s", ege::graphic::font::library::getErrorMessage( error ) );

        FT_Int major, minor, patch;
        FT_Library_Version( ege::graphic::font::library::instance, &major, &minor, &patch );

        engine::resources->logger->log( util::log::Level::INFO, "FreeType %d.%d.%d initialized", major, minor, patch );
}


void ege::graphic::font::library::destroy()
{
        if ( !initialized.exchange( false ) )
                ege::exception::throwNew( "FreeType library was already destroyed (or was never initialized)" );

        FT_Done_FreeType( ege::graphic::font::library::instance );
}
