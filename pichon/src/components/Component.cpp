#include "components/Component.h"
#include "components/ComponentManager.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

Component::Component(GameObject *owner, IComponentManager *manager_) : m_manager(validateManager(manager_))
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

IComponentManager *Component::validateManager(IComponentManager *manager)
{
    if (manager == nullptr)
    {
        throw std::runtime_error{"Attemp to give a null ComponentManager object!"};
    }
    return manager;
}

IComponentManager *Component::manager() const
{
    return m_manager;
}

