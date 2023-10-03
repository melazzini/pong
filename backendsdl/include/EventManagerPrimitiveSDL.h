#pragma once
#include "BackendContextInterface.h"
#include "IPrimitives.h"

struct EventManagerPrimitiveSDL : IEventManagerPrimitive
{
    void pollEvents(IEventManager &eventManager) const override;
    bool isKeyPressed(Keyboard key) const override;
};

struct EventManagerPrimitiveProviderSDL : backendContext::IEventManagerPrimitiveProvider
{
    std::unique_ptr<IEventManagerPrimitive> provide() const override
    {
        return std::make_unique<EventManagerPrimitiveSDL>();
    }
};
