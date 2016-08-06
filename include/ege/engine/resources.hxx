

#ifndef EGE_ENGINE_RESOURCES_HXX
#define EGE_ENGINE_RESOURCES_HXX


#include <ege/graphic/canvas.hxx>
#include <ege/resource/manager.hxx>


namespace ege
{
        namespace engine
        {
                struct Resources
                {
                        graphic::Canvas* screen;
                        resource::Manager* resourcesManager;
                };
        }
}


#endif
