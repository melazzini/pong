#include "Window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

struct DummyRendererPrimitive : IRendererPrimitive
{
};

struct DummyWindowPrimitive : IWindowPrimitive
{
    void clearWindow(glm::u8vec4 color) override
    {
    }

    void updateWindow() override
    {
    }
};

struct DummyBackendContext : IBackendContext
{
    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        return std::make_unique<DummyRendererPrimitive>();
    }

    std::unique_ptr<IWindowPrimitive> windowPrimitive() override
    {
        return std::make_unique<DummyWindowPrimitive>();
    }
};

TEST(AWindow, IsASingleton)
{
    DummyBackendContext engine;
    Window *wnd1 = Window::getInstance(&engine);
    Window *wnd2 = Window::getInstance(&engine);
    ASSERT_THAT(wnd1, Eq(wnd2));
}

struct TheWindow : testing::Test
{
    DummyBackendContext engine;
    Window *wnd{Window::getInstance(&engine)};
};

TEST_F(TheWindow, CanClearItsContents)
{
    wnd->clear(glm::u8vec4(0, 0, 0, 255));
}

TEST_F(TheWindow, CanPresentARenderer)
{
    wnd->present();
}
