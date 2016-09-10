

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
                                        bool vSyncEnabled;
                                        float period;
                                        float periodFactor;

                                public:
                                        Moderator( Analyzer& analyzer, float fps = 60.0f, bool vSyncEnabled = false );
                                        void setFPS( float fps );
                                        void setVSyncEnabled( bool vSyncEnabled );
                                        void moderate();
                        };
                }
        }
}


#endif
