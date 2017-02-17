
#ifndef EGE_LOG_HXX
#define EGE_LOG_HXX

/**
 * \namespace ege::log
 * \brief Contains the classes used to perform logging.
 * */

#include <mutex>
#include <ostream>
#include <string>

namespace ege
{
    namespace log
    {
        /**
         * \brief Enumeration of the log levels.
         * */
        enum class Level
        {
            DEBUG       = 0,
            INFO        = 1,
            WARNING     = 2,
            ERROR       = 3,
            FATAL       = 4,
            DEFAULT     = INFO
        };

        /**
         * \brief Performs actual logging.
         *
         * Any time a log is performed on a level (or more precisely on his stream). That can be:
         *  - \b DEBUG: When debugging.
         *  - \b INFO: When all is ok. Just logging for having fun.
         *  - \b WARNING: When something is not as it should be.
         *  - \b ERROR: When something bad happens.
         *  - \b FATAL: When something \b very bad happens.
         *
         * Each log level have a specified stream on which log on. By default DEBUG, INFO and WARNING levels will
         * log to \c std::cout, likewise ERROR and FATAL will log to \c std::cerr. If you don't like log to those,
         * change them with Logger::setStream(). \n
         * Example of use:
         *
         * \code
         * using namespace ege::log;
         * Logger logger;
         * logger.log(Level::DEBUG, "%d + %d = %d", 5, 7, 5 + 7);
         * \endcode
         *
         * \sa Logger::log()
         * */
        class Logger
        {
            private:
                std::ostream* streams[5];

                /**
                 * \brief Used to synchronize multiple logs.
                 * */
                std::mutex mutex;

            public:

                /**
                 * \brief Create a new default Logger.
                 * */
                Logger();

                /**
                 * \brief Log the string represented by the formatted one on the desired log Level Stream.
                 * \param level The desired log Level.
                 * \param formatted The string formatted using a printf-like syntax.
                 * \param ... The arguments for the formatted string.
                 * */
                void log(Level level, const std::string& formatted, ...);

                /**
                 * \brief Change the log Stream at a specified log Level.
                 *
                 * Note that the Logger won't manage the deletion of the stream, thus if a stream is deleted
                 * then the pointer to that stream have to be removed for the specific level (replaced
                 * by another stream for example).
                 *
                 * \param level The log Level where change the stream.
                 * \param stream The new Stream for the specified level.
                 * \return The reference of the same logger.
                 * */
                Logger& setStream(Level level, std::ostream* stream);
        };

        /**
         * \brief Returns a string, that represent the specified Level.
         *
         * For example:
         *      - Level::DEBUG will return "debug".
         *      - Level::INFO will return "info".
         *      - ...
         *
         * \param level The specified level.
         * \return The string representing it.
         * */
        std::string to_string(Level level);
    }
}

#endif
