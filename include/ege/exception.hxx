

#ifndef EGE_EXCEPTION_HXX
#define EGE_EXCEPTION_HXX


#include <exception>
#include <string>


namespace ege
{
        namespace exception
        {
                void throwNew( std::string const& formatted, ... );
        }

        class Exception: public std::exception
        {
                friend void ege::exception::throwNew( std::string const& formatted, ... );

                private:
                        const std::string message;

                        Exception( std::string const& message );

                public:
                        virtual ~Exception();
                        virtual const char* what() const throw();
                        void consume();
        };
}


#endif
