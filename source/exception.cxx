#include <ege/exception.hxx>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ege/engine.hxx>


ege::Exception::Exception( std::string const& message ):
        message( message )
{

}


ege::Exception::~Exception()
{

}


const char* ege::Exception::what() const throw()
{
        return message.c_str();
}


void ege::Exception::consume()
{
        ege::engine::resources->logger->log( ege::util::log::Level::ERROR, what() );
}


void ege::exception::throwNew( std::string const& formatted, ... )
{
        va_list args;
        va_start( args, formatted );
        char* ptr;

        if ( vasprintf( &ptr, formatted.c_str(), args ) == -1 )
                throw Exception( "exception and later out of memory occoured" );

        va_end( args );
        std::string message( ptr );
        std::free( ptr );
        throw Exception( message );
}
