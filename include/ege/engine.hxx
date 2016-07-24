

#ifndef EGE_ENGINE_HXX
#define EGE_ENGINE_HXX


#include <ege/graphic/canvas.hxx>
#include <ege/scenario.hxx>


namespace ege
{
        class Scenario;

        struct EngineResources
        {
                ege::graphic::Canvas* screen;
        };

        class Engine
        {
                private:
                        void* win;
                        EngineResources* resources;

                        Engine();

                public:
                        virtual ~Engine();
                        void start( Scenario* initialScenario );
                        EngineResources* getResources();
                        static Engine& getReference();
        };
}


#endif
