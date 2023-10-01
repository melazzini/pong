#pragma once
#include "IPrimitives.h"

namespace backendContext
{
struct IEventManagerPrimitiveProvider
{
    virtual std::unique_ptr<IEventManagerPrimitive> provide() const = 0;
    virtual ~IEventManagerPrimitiveProvider() = default;
};
} // namespace backendContext
