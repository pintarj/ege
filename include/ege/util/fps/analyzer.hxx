

#ifndef EGE_UTIL_FPS_ANALYZER_HXX
#define EGE_UTIL_FPS_ANALYZER_HXX


#include <chrono>


namespace ege
{
        namespace util
        {
                namespace fps
                {
                        class Analyzer
                        {
                                private:
                                        std::chrono::time_point< std::chrono::system_clock > lastTimePoint;
                                        std::chrono::duration< float > lastDelta;

                                public:
                                        Analyzer( float lastDelta = 0.0f );
                                        void markTimePoint();
                                        float calculateDelta();
                                        void setLastDelta( float lastDelta );
                                        float getLastDelta();
                        };
                }
        }
}


#endif