

#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX


#include <ege/scenario.hxx>


namespace ege
{
        class Engine
        {
                private:
                        void* win;

                public:
                        Engine();
                        virtual ~Engine();
                        void start( Scenario* initialScenario );
        };
}


#endif
