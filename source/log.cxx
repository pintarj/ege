#include <ege/log.hxx>
#include <chrono>
#include <cstdarg>
#include <cstring>
#include <ctime>
#include <iostream>
#include <ege/exception.hxx>

namespace ege
{
    namespace log
    {
        Logger::Logger()
        {
            setStream(Level::DEBUG, &std::cout);
            setStream(Level::INFO, &std::cout);
            setStream(Level::WARNING, &std::cout);
            setStream(Level::ERROR, &std::cerr);
            setStream(Level::FATAL, &std::cerr);
        }

        void Logger::log(Level level, const std::string& formatted, ...)
        {
            std::ostream* stream = streams[(unsigned) level];

            if (stream == nullptr)
                return;

            va_list args;
            va_start(args, formatted);
            char* result;

            if (vasprintf(&result, formatted.c_str(), args) == -1)
                ege::exception::throwNew("out of memory");

            va_end(args);
            using namespace std::chrono;
            auto now = system_clock::now();
            std::time_t time_struct = system_clock::to_time_t(now);
            std::tm* info = std::localtime(&time_struct);
            int hours = info->tm_hour;
            int minutes = info->tm_min;
            int seconds = info->tm_sec;
            int micros = (int) (now.time_since_epoch() / std::chrono::microseconds(1) % 1000000);
            char time[16];
            sprintf(time, "%02d:%02d:%02d.%06d", hours, minutes, seconds, micros);
            *stream << "[" << time << "] [" << to_string(level) << "] ";
            static const std::string indentation(26, ' ');
            char* ptr = result;

            while (true)
            {
                char* match = std::strchr(ptr, '\n');

                if (match == nullptr)
                    break;

                *match = '\0';
                *stream << ptr << std::endl << indentation;
                ptr = match + 1;
            }

            *stream << ptr << std::endl;
            std::free(result);
        }

        Logger& Logger::setStream(Level level, std::ostream* stream)
        {
            streams[(unsigned) level] = stream;
            return *this;
        }

        std::string to_string(Level level)
        {
            switch (level)
            {
                case Level::DEBUG:
                    return "debug";

                case Level::INFO:
                    return "info";

                case Level::WARNING:
                    return "warning";

                case Level::ERROR:
                    return "error";

                case Level::FATAL:
                    return "fatal";
            }
        }
    }
}
