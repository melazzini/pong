#pragma once
#include "GameInterfaces.h"
#include <vector>

struct GameLoop : IGameLoop
{
    bool running{false};

    bool initialize() override
    {
        return false;
    }

    void handleInput(IEventManager *eventManager) override;

    void update(uint32_t deltatime, IGameObjectsManager *gameObjectsManager) override;

    void generateOutput(IGameObjectsManager *gameObjectsManager) override;

    void destroy(IGameObjectsManager *gameObjectsManager) override;
};
