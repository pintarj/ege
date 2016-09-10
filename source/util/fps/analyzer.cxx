#include <ege/util/fps/analyzer.hxx>


using namespace ege::util::fps;


Analyzer::Analyzer( float lastDelta )
{
        markedTimePoint = std::chrono::system_clock::now();
        setLastDelta( lastDelta );
}


float Analyzer::calculateDelta( bool mark )
{
        std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
        lastDelta = now - markedTimePoint;

        if ( mark )
                markedTimePoint = now;

        return lastDelta.count();
}


float Analyzer::calculateDeltaAndMark()
{
        return calculateDelta( true );
}


void Analyzer::setLastDelta( float lastDelta )
{
        this->lastDelta = std::chrono::duration< float >( lastDelta );
}


float Analyzer::getLastDelta()
{
        return lastDelta.count();
}
