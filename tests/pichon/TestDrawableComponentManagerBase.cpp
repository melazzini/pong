#include "Drawable.h"
#include "GameObject.h"
#include "Interfaces.h"
#include "MockRenderer.h"
#include "components/DrawableComponent.h"
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

struct MockDrawableComponent : DrawableComponent
{
    MockDrawableComponent(GameObject *owner, DrawableComponentManagerBase *manager) : DrawableComponent{owner, manager}
    {
    }
    MOCK_METHOD(void, draw, (), (override));
};

TEST(ADrawableComponentManagerBase, UsesItsRendererToDrawDrawables)
{
    MockRenderer renderer;
    DrawableComponentManagerBase drawableComponentManager{&renderer};
    DummyDrawable dummyDrawable{nullptr};
    EXPECT_CALL(renderer, render);
    drawableComponentManager.draw(&dummyDrawable);
}

TEST(ADrawableComponentManagerBase, PaintAllItsDrawableComponents)
{
    GameObject dummyGameObject;
    MockRenderer renderer;
    DrawableComponentManagerBase drawableComponentManager{&renderer};
    MockDrawableComponent drawable{&dummyGameObject, &drawableComponentManager};
    drawableComponentManager.registerComponent(&drawable);
    EXPECT_CALL(drawable, draw);
    drawableComponentManager.paintComponents();
}
