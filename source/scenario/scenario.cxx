#include <ege/scenario/scenario.hxx>


using namespace ege::scenario;


Scenario::Scenario()
{
        nextScenario = nullptr;
        nextScenarioAvailable = false;
}


void Scenario::setNextScenario( Scenario* scenario )
{
        nextScenario = scenario;
        nextScenarioAvailable = true;
}


void Scenario::setEndAsNextScenario()
{
        setNextScenario( nullptr );
}


Scenario::~Scenario()
{

}


bool Scenario::isNextScenarioAvailable()
{
        return nextScenarioAvailable;
}


Scenario* Scenario::getNextScenario()
{
        return nextScenario;
}


void Scenario::update( float delta )
{

}


void Scenario::render()
{

}


void Scenario::shouldClose()
{
        setEndAsNextScenario();
}
