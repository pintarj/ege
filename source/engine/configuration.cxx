#include <ege/engine/configuration.hxx>
#include <ege/engine/resources.hxx>

namespace ege
{
    namespace engine
    {
        Configuration::WindowCreation::WindowCreation()
        {
            width = 800;
            height = 600;
            resizable = true;
        }

        const std::string Configuration::getApplicationName()
        {
            return "EGE application";
        }

        bool Configuration::skipStartScene()
        {
            return false;
        }

        bool Configuration::isFullscreenPreferred()
        {
            return true;
        }

        const hardware::VideoMode& Configuration::getPreferredVideoMode()
        {
            return engine::getPrimaryMonitor().getCurrentVideoMode();
        }

        Configuration::WindowCreation Configuration::getPreferredWindowCreationParams()
        {
            return Configuration::WindowCreation();
        }
    }
}
