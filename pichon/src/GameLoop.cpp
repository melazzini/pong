#include "GameLoop.h"
#include "components/Component.h"
#include <algorithm>
#include <vector>

void GameLoop::update(uint32_t deltatime, const std::vector<ComponentManager *> &managers)
{
    std::for_each(std::begin(managers), std::end(managers),
                  [deltatime](ComponentManager *manager) { manager->update(deltatime); });
}

void GameLoop::output(const std::vector<OutputComponentManager *> &outputComponentManagers)
{
    std::for_each(std::begin(outputComponentManagers), std::end(outputComponentManagers),
                  [](OutputComponentManager *manager) { manager->output(); });
}
