#include <ege/exception.hxx>
#include <exception>
#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>


using namespace ege;


class EgeException: public std::exception
{
        private:
                const char* message;

        public:
                EgeException( const char* message ): message( message )
                {

                }

                virtual ~EgeException()
                {
                        std::free( ( void* ) message );
                }

                const char* what() const throw()
                {
                        return message;
                }
};


void exception::throwNew( const char * formatted, ... )
{
        va_list args;
        va_start( args, formatted );
        char* message;
        vasprintf( &message, formatted, args );
        va_end( args );
        throw new EgeException( message );
}
