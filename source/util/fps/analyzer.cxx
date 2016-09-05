#include <ege/util/fps/analyzer.hxx>


using namespace ege::util::fps;


Analyzer::Analyzer( float lastDelta )
{
        lastTimePoint = std::chrono::system_clock::now();
        setLastDelta( lastDelta );
}


void Analyzer::markTimePoint()
{
        std::chrono::time_point< std::chrono::system_clock > currentTimePoint = std::chrono::system_clock::now();
        lastDelta = currentTimePoint - lastTimePoint;
        lastTimePoint = currentTimePoint;
}


float Analyzer::calculateDelta()
{
        lastDelta = std::chrono::system_clock::now() - lastTimePoint;
        return lastDelta.count();
}


void Analyzer::setLastDelta( float lastDelta )
{
        this->lastDelta = std::chrono::duration< float >( lastDelta );
}


float Analyzer::getLastDelta()
{
        return lastDelta.count();
}
