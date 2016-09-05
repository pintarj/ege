#include <ege/util/fps/moderator.hxx>
#include <thread>


using namespace ege::util::fps;


Moderator::Moderator( Analyzer &analyzer, float fps, bool vSyncEnabled ): analyzer( analyzer )
{
        setFPS( fps );
        setVSyncEnabled( vSyncEnabled );
}


void Moderator::setFPS( float fps )
{
        this->fps = fps;
        period = 1.0f / fps;
}


void Moderator::moderate()
{
        float delta = analyzer.calculateDelta();
        float excess = period * periodFactor - delta;

        if ( excess < 0.0f )
                return;

        std::this_thread::sleep_for( std::chrono::duration< float >( excess ) );
}


void Moderator::setVSyncEnabled( bool vSyncEnabled )
{
        this->vSyncEnabled = vSyncEnabled;
        periodFactor = ( vSyncEnabled ? 0.8f : 1.0f );
}
