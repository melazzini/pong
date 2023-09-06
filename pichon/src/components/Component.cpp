#include "components/Component.h"
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

void ComponentManager::update(float deltatime)
{
    for (auto component : m_components)
    {
        component->update(deltatime);
    }
}
