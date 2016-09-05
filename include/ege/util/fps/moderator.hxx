

#ifndef EGE_UTIL_FPS_MODERATOR_HXX
#define EGE_UTIL_FPS_MODERATOR_HXX


#include <ege/util/fps/analyzer.hxx>


namespace ege
{
        namespace util
        {
                namespace fps
                {
                        class Moderator
                        {
                                private:
                                        Analyzer& analyzer;
                                        float fps;
                                        float period;
                                        bool vSyncEnabled;
                                        float periodFactor;

                                public:
                                        Moderator( Analyzer& analyzer, float fps = 60.0f, bool vSyncEnabled );
                                        void setFPS( float fps );
                                        void moderate();
                                        void setVSyncEnabled( bool vSyncEnabled );
                        };
                }
        }
}


#endif
