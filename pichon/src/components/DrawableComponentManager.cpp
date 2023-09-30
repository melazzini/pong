#include "Interfaces.h"
#include "components/DrawableComponent.h"
#include <algorithm>

DrawableComponentManager *DrawableComponentManager::getInstance(IRenderer *renderer)
{
    static DrawableComponentManager instance{renderer};
    return &instance;
}

void DrawableComponentManagerBase::updateComponents(uint32_t deltatime)
{
    for (auto component : m_components)
    {
        component->update(deltatime);
    }
}

void DrawableComponentManagerBase::destroyComponents()
{
    for (auto component : m_components)
    {
        // component->destroy();
    }
}

bool DrawableComponentManagerBase::hasComponent(IComponent *component) const
{
    if (auto drawable{dynamic_cast<DrawableComponent *>(component)}; drawable)
    {
        return std::find(std::begin(m_components), std::end(m_components),
                         dynamic_cast<DrawableComponent *>(component)) != std::end(m_components);
    }
    return false;
}

bool DrawableComponentManagerBase::registerComponent(IComponent *component)
{
    if (auto drawable{dynamic_cast<DrawableComponent *>(component)}; drawable)
    {
        m_components.push_back(drawable);
    }
    return false;
}

void DrawableComponentManagerBase::output()
{
    for (auto component : m_components)
    {
        component->draw();
    }
}

