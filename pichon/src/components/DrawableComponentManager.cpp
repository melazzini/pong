#include "Interfaces.h"
#include "components/DrawableComponent.h"

DrawableComponentManager *DrawableComponentManager::getInstance(IRenderer *renderer)
{
    static DrawableComponentManager instance{renderer};
    return &instance;
}

void DrawableComponentManagerBase::paintComponents()
{
    for (auto component : m_components)
    {
        if (auto drawableComponent{dynamic_cast<DrawableComponent *>(component)}; drawableComponent)
        {
            drawableComponent->draw();
        }
    }
}
