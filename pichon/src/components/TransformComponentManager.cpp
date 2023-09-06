#include "components/TransformComponent.h"

TransformComponentManager *TransformComponentManager::getInstance()
{
    static TransformComponentManager instance;
    return &instance;
}
