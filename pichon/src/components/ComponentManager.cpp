#include "components/ComponentManager.h"
#include <algorithm>

ComponentManager::ComponentManager(bool (*componentValidator)(IComponent *)) : m_componentValidator(componentValidator)
{
}

bool ComponentManager::registerComponent(IComponent *component)
{
    if (m_componentValidator(component))
    {
        m_components.push_back(component);
        return true;
    }
    return false;
}

void ComponentManager::updateComponents(uint32_t deltatime)
{
    for (auto component : m_components)
    {
        component->update(deltatime);
    }
}

void ComponentManager::destroyComponents()
{
}

bool ComponentManager::hasComponent(IComponent *component) const
{
    return std::find(std::begin(m_components), std::end(m_components), component) != std::end(m_components);
}
