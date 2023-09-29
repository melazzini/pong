#include "components/Component.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

Component::Component(GameObject *owner, ComponentManager *manager_) : m_manager(validateManager(manager_))
{
    auto owner_{validateOwner(owner)};
}

GameObject *Component::validateOwner(GameObject *owner)
{
    if (owner == nullptr)
    {
        throw std::runtime_error{"Attemp to give a null GameObject-owner!"};
    }
    return owner;
}

ComponentManager *Component::validateManager(ComponentManager *manager)
{
    if (manager == nullptr)
    {
        throw std::runtime_error{"Attemp to give a null ComponentManager object!"};
    }
    return manager;
}

ComponentManager *Component::manager() const
{
    return m_manager;
}

void ComponentManager::update(uint32_t deltatime)
{
    for (auto component : m_components)
    {
        component->update(deltatime);
    }
}

bool ComponentManager::hasComponent(IComponent *component) const
{
    return std::find(std::begin(m_components), std::end(m_components), component) != std::end(m_components);
}
