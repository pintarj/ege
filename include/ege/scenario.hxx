

#ifndef EGE_SCENARIO_HXX
#define EGE_SCENARIO_HXX


#include <ege/engine.hxx>


namespace ege
{
        struct EngineResources;

        class Scenario
        {
                private:
                        Scenario* nextScenario;
                        bool nextScenarioAvailable;

                protected:
                        EngineResources* engineResources;

                        Scenario();
                        void setNextScenario( Scenario* scenario );
                        void setEndAsNextScenario();

                public:
                        virtual ~Scenario() {};
                        bool isNextScenarioAvailable();
                        Scenario* getNextScenario();
                        virtual void update();
                        virtual void shouldClose();
        };
}


#endif
