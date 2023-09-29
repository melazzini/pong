#include "GameLoop.h"
#include "components/Component.h"
#include <algorithm>

void GameLoop::update(uint32_t deltatime, const std::vector<ComponentManager *> &managers)
{
    std::for_each(std::begin(managers), std::end(managers),
                  [deltatime](ComponentManager *manager) { manager->update(deltatime); });
}
