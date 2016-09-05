#include <ege/exception.hxx>
#include <exception>
#include <cstring>
#include <cstddef>


using namespace ege;


class EgeException: public std::exception
{
        private:
                char* message;
                bool copy;

        public:
                EgeException( const char* message, bool copy )
                {
                        if ( copy )
                        {
                                size_t length = std::strlen( message );
                                this->message = new char[ length + 1 ];
                                std::memcpy( this->message, message, length );
                                this->message[ length ] = '\0';
                        }
                        else
                        {
                                this->message = ( char* ) message;
                        }
                }

                virtual ~EgeException()
                {
                        if ( copy )
                                delete message;
                }

                const char* what() const throw()
                {
                        return message;
                }
};


void exception::throwNew( const char* message, bool copy )
{
        throw new EgeException( message, copy );
}
