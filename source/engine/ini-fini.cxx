#include <private/ege/engine/ini-fini.hxx>
#include <algorithm>
#include <deque>

namespace ege
{
    namespace engine
    {
        static std::deque<IniFini*>* iniFinis = nullptr;
        static unsigned referenceCounter = 0;

        IniFini::IniFini()
        {
            if (iniFinis == nullptr)
                iniFinis = new std::deque<IniFini*>();

            iniFinis->push_back(this);
            ++referenceCounter;
        }
        
        IniFini::~IniFini()
        {
            --referenceCounter;
            
            if (referenceCounter == 0)
            {
                delete iniFinis;
                iniFinis = nullptr;
            }
        }

        void IniFini::initialize()
        {

        }

        void IniFini::terminate()
        {

        }

        namespace iniFini
        {
            void initialize()
            {
                std::for_each(iniFinis->begin(), iniFinis->end(), [](IniFini* iniFini)
                    {
                       iniFini->initialize();
                    });
            }

            void terminate()
            {
                std::for_each(iniFinis->rbegin(), iniFinis->rend(), [](IniFini* iniFini)
                    {
                        iniFini->terminate();
                    });
            }
        }
    }
}
