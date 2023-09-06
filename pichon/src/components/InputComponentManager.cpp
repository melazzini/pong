#include "EventManagementInterface.h"
#include "components/InputComponent.h"

InputComponentManager *InputComponentManager::getInstance(IEventManager *eventManager)
{
    static InputComponentManager instance{eventManager};
    return &instance;
}
