

#ifndef EGE_UTIL_LOG_LEVEL_HXX
#define EGE_UTIL_LOG_LEVEL_HXX


namespace ege
{
        namespace util
        {
                namespace log
                {
                        enum class Level
                        {
                                DEBUG = 0,
                                INFO = 1,
                                WARNING = 2,
                                ERROR = 3,
                                FATAL = 4
                        };

                        namespace level
                        {
                                constexpr const char* toString( Level level )
                                {
                                        switch ( level )
                                        {
                                                case Level::DEBUG:
                                                        return "DEBUG";

                                                case Level::INFO:
                                                        return "INFO";

                                                case Level::WARNING:
                                                        return "WARNING";

                                                case Level::ERROR:
                                                        return "ERROR";

                                                case Level::FATAL:
                                                        return "FATAL";
                                        }
                                }
                        }
                }
        }
}


#endif
