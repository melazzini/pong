#include "Drawable.h"
#include "Interfaces.h"
#include "MockRenderer.h"
#include "components/DrawableComponent.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Ne;
using testing::Return;

struct DummyDrawable : Drawable
{
    DummyDrawable(std::unique_ptr<IDrawablePrimitive> primitive) : Drawable(std::move(primitive))
    {
    }

    void draw() override
    {
    }
};

TEST(ADrawableComponentManagerBase, UsesItsRendererToDrawDrawables)
{
    MockRenderer renderer;
    DrawableComponentManagerBase drawableComponentManager{&renderer};
    DummyDrawable dummyDrawable{nullptr};
    EXPECT_CALL(renderer, render);
    drawableComponentManager.draw(&dummyDrawable);
}
