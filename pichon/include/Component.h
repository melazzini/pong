#pragma once

struct Component
{
    virtual void update(float deltaTime) = 0;

    virtual ~Component() = default;
};
