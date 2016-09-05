

#ifndef EGE_SCENARIO_HXX
#define EGE_SCENARIO_HXX


#include <ege/engine/engine.hxx>


namespace ege
{
        struct EngineResources;

        class Scenario
        {
                private:
                        Scenario* nextScenario;
                        bool nextScenarioAvailable;

                protected:
                        Scenario();
                        void setNextScenario( Scenario* scenario );
                        void setEndAsNextScenario();

                public:
                        virtual ~Scenario() {};
                        bool isNextScenarioAvailable();
                        Scenario* getNextScenario();
                        virtual void update( float delta );
                        virtual void render();
                        virtual void shouldClose();
        };
}


#endif
