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

    void handleInput() override
    {
    }

    void update(uint32_t deltatime, const std::vector<ComponentManager *> &managers) override;

    void output() override
    {
    }

    void destroy() override
    {
    }
};
