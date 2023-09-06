#include "components/BoxColliderComponent.h"

BoxColliderComponentManager *BoxColliderComponentManager::getInstance()
{
    static BoxColliderComponentManager instance;
    return &instance;
}
