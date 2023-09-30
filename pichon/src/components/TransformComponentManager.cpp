#include "components/TransformComponent.h"

TransformComponentManager *TransformComponentManager::getInstance()
{
    static TransformComponentManager instance;
    return &instance;
}
bool TransformComponentManager::registerComponent(IComponent *component)
{
    if (component)
    {
        m_components.push_back(component);
        return true;
    }
    return false;
}
bool TransformComponentManager::hasComponent(IComponent *component) const
{
    return std::find(std::begin(m_components), std::end(m_components), component) != std::end(m_components);
}
void TransformComponentManager::updateComponents(uint32_t deltatime)
{
    std::for_each(std::begin(m_components), std::end(m_components),
                  [deltatime](IComponent *component) { component->update(deltatime); });
}
void TransformComponentManager::destroyComponents()
{
    std::for_each(std::begin(m_components), std::end(m_components), [](IComponent *component) {
        // TODO: component->destroy()
    });
}
