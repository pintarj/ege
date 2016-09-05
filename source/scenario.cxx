#include <ege/scenario.hxx>


using namespace ege;


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


void Scenario::shouldClose()
{
        setEndAsNextScenario();
}
