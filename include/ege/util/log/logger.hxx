

#ifndef EGE_UTIL_LOG_LOGGER_HXX
#define EGE_UTIL_LOG_LOGGER_HXX


#include <ege/util/log/level.hxx>


namespace ege
{
        namespace util
        {
                namespace log
                {
                        class Logger
                        {
                                private:
                                        Level level;

                                public:
                                        Logger( Level level = Level::INFO );
                                        virtual ~Logger() {};
                                        void setLevel( Level level );
                                        void log( Level level, const char * formatted, ... ) const;
                        };
                }
        }
}


#endif
