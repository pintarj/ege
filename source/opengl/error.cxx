#include <ege/opengl/error.hxx>
#include <GL/glew.h>
#include <ege/exception.hxx>
#include <ege/engine/resources.hxx>

namespace ege
{
    namespace opengl
    {
        Error getError()
        {
            return (Error) glGetError();
        }

        std::string toString(Error error) noexcept
        {
            switch (error)
            {
                case Error::NO_ERROR:
                    return "NO_ERROR";

                case Error::INVALID_ENUM:
                    return "INVALID_ENUM";

                case Error::INVALID_OPERATION:
                    return "INVALID_OPERATION";

                case Error::STACK_OVERFLOW:
                    return "STACK_OVERFLOW";

                case Error::STACK_UNDERFLOW:
                    return "STACK_UNDERFLOW";

                case Error::OUT_OF_MEMORY:
                    return "OUT_OF_MEMORY";

                case Error::INVALID_FRAMEBUFFER_OPERATION:
                    return "INVALID_FRAMEBUFFER_OPERATION";

                case Error::CONTEXT_LOST:
                    return "CONTEXT_LOST";

                case Error::TABLE_TOO_LARGE:
                    return "TABLE_TOO_LARGE";

                default:
                    return "UNKNOWN";
            }
        }

        void checkError(const std::string& message, bool throwOnError)
        {
            Error error = getError();

            if (error != Error::NO_ERROR)
            {
                if (throwOnError)
                    exception::throwNew("%s (%d, %s)", message.c_str(), (int) error, toString(error).c_str());
                else
                    engine::getLogger().log(log::Level::ERROR, "%s (%d, %s)", message.c_str(), (int) error, toString(error).c_str());
            }
        }
    }
}
