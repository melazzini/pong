#pragma once
#include "EventManagementInterface.h"

namespace backendContext
{
struct IEventManagerPrimitiveProvider
{
    virtual std::unique_ptr<IEventManagerPrimitive> provide() const = 0;
};
} // namespace backendContext
