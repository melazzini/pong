#pragma once
#include "Interfaces.h"
#include <gmock/gmock.h>

struct MockRenderer : IRenderer
{
    MOCK_METHOD(void, render, (Drawable *), (override));
    IRendererPrimitive *primitive() override
    {
        return nullptr;
    }
};
