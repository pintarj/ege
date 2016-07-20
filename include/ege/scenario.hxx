

#ifndef EGE_SCENARIO_HXX
#define EGE_SCENARIO_HXX


namespace ege
{
        class Scenario
        {
                private:
                        Scenario* nextScenario;
                        bool nextScenarioAvailable;

                protected:
                        void setNextScenario( Scenario* scenario );
                        void setEndAsNextScenario();

                public:
                        Scenario();
                        virtual ~Scenario() {};
                        bool isNextScenarioAvailable();
                        Scenario* getNextScenario();
                        virtual void update();
                        virtual void shouldClose();
        };
}


#endif
