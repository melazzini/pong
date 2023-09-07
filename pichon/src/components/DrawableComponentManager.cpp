#include "Interfaces.h"
#include "components/DrawableComponent.h"

DrawableComponentManager *DrawableComponentManager::getInstance(IRenderer *renderer)
{
    static DrawableComponentManager instance{renderer};
    return &instance;
}
