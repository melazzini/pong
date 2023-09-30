#include "EventManagementInterface.h"
#include "components/InputComponent.h"
#include <algorithm>

InputComponentManager *InputComponentManager::getInstance(IEventManager *eventManager)
{
    static InputComponentManager instance{eventManager};
    return &instance;
}

bool InputComponentManagerBase::registerComponent(IComponent *component)
{
    if (component)
    {
        m_components.push_back(component);
        return true;
    }
    return false;
}
bool InputComponentManagerBase::hasComponent(IComponent *component) const
{
    return std::find(std::begin(m_components), std::end(m_components), component) != std::end(m_components);
}
void InputComponentManagerBase::updateComponents(uint32_t deltatime)
{
    std::for_each(std::begin(m_components), std::end(m_components),
                  [deltatime](IComponent *component) { component->update(deltatime); });
}
void InputComponentManagerBase::destroyComponents()
{
    std::for_each(std::begin(m_components), std::end(m_components), [](IComponent *component) {
        // TODO: component->destroy()
    });
}
