#include "components/DrawableComponent.h"

DrawableComponentManager *DrawableComponentManager::getInstance()
{
    static DrawableComponentManager instance;
    return &instance;
}
