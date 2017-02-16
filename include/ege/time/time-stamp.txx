#include <thread>

namespace ege
{
    namespace time
    {
        template<typename T, class P, class C>
        TimeStamp<T, P, C>::TimeStamp(std::chrono::time_point<C> timePoint):
            timePoint(timePoint)
        {

        }

        template<typename T, class P, class C>
        T TimeStamp<T, P, C>::getElapsed() const
        {
            auto now = C::now();
            auto duration = std::chrono::duration_cast<std::chrono::duration<T, P>>(now - timePoint);
            return duration.count();
        }

        template<typename T, class P, class C>
        T TimeStamp<T, P, C>::waitUntil(T elapsed) const
        {
            T reallyElapsed = getElapsed();
            T difference = elapsed - reallyElapsed;

            if (difference < 0)
                return (T) 0;

            std::this_thread::sleep_for(std::chrono::duration<T, P>(difference));
            return getElapsed() - reallyElapsed;
        }
    }
}
