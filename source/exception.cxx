#include <ege/exception.hxx>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ege/engine.hxx>

namespace ege
{
    Exception::Exception(const std::string& message):
        message(message)
    {

    }

    Exception::~Exception()
    {

    }

    const char* Exception::what() const throw()
    {
        return message.c_str();
    }

    void Exception::consume()
    {
        engine::resources->logger->log(ege::log::Level::ERROR, what());
    }

    namespace exception
    {
        void throwNew(const std::string& formatted, ...)
        {
            va_list args;
            va_start(args, formatted);
            char* ptr;

            if (vasprintf(&ptr, formatted.c_str(), args) == -1)
                throw Exception("exception and later out of memory occoured");

            va_end(args);
            std::string message(ptr);
            std::free(ptr);
            throw Exception(message);
        }
    }
}
