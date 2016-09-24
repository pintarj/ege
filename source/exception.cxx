#include <ege/exception.hxx>
#include <exception>
#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <ege/engine.hxx>


using namespace ege;


Exception::Exception( const char* message ): message( message )
{

}


const char* Exception::what() const throw()
{
        return message;
}


void Exception::consume()
{
        engine::resources->logger->log( util::log::Level::ERROR, what() );
        delete this;
}


void Exception::throwNew( const char * formatted, ... )
{
        va_list args;
        va_start( args, formatted );
        char* message;
        vasprintf( &message, formatted, args );
        va_end( args );
        throw new Exception( message );
}
