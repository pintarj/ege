#include <ege/util/log/logger.hxx>
#include <chrono>
#include <cstdarg>
#include <iostream>
#include <mutex>
#include <cstring>


using namespace ege::util::log;


Logger::Logger( Level level )
{
        setLevel( level );
}


void Logger::setLevel( Level level )
{
        this->level = level;
}


void Logger::log( Level level, const char* formatted, ... ) const
{
        if ( level < this->level )
                return;

        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t( now );
        std::ostream& out = level < Level::ERROR ? std::cout : std::cerr;
        char* log;
        va_list args;
        va_start( args, formatted );
        vasprintf( &log, formatted, args );
        va_end( args );

        {
                static std::mutex mutex;
                std::unique_lock< std::mutex > lock( mutex );
                std::tm* info = std::localtime( &time );

                char hours = ( char ) info->tm_hour;
                char minutes = ( char ) info->tm_min;
                char seconds = ( char ) info->tm_sec;
                int micros = ( int ) ( now.time_since_epoch() / std::chrono::microseconds( 1 ) % 1000000 );
                char buf[ 32 ];
                sprintf( buf, "[ %02hhd:%02hhd:%02hhd.%06d ][ %-7s ] ", hours, minutes, seconds, micros, level::toString( level ) );
                out << buf;

                char* ptr = log;

                while ( true )
                {
                        char* match = std::strchr( ptr, '\n' );

                        if ( match == nullptr )
                                break;

                        *match = '\0';
                        out << ptr << std::endl << std::string( 31, ' ' );
                        ptr = match + 1;
                }

                out << ptr << std::endl;
        }

        std::free( static_cast< void* >( log ) );
}
