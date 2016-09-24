

#ifndef EGE_EXCEPTION_HXX
#define EGE_EXCEPTION_HXX


#include <exception>


namespace ege
{
        class Exception: public std::exception
        {
                private:
                        const char* message;

                        Exception( const char* message );

                public:
                        virtual ~Exception() {};
                        virtual const char* what() const throw();
                        void consume();
                        static void throwNew( const char * formatted, ... );
        };
}


#endif
