#include "Window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using testing::Eq;
using testing::Ne;

struct DummyRendererPrimitive : IRendererPrimitive
{
};

struct DummyBackendContext : IBackendContext
{
    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        return std::make_unique<DummyRendererPrimitive>();
    }
};

static DummyBackendContext engine;

struct DummyRenderer : IRenderer
{
    void render(Drawable *)
    {
    }
    IRendererPrimitive *primitive()
    {
        return nullptr;
    }
};

TEST(AWindow, IsASingleton)
{
    Window *wnd1 = Window::getInstance(&engine);
    Window *wnd2 = Window::getInstance(&engine);
    ASSERT_THAT(wnd1, Eq(wnd2));
}

struct TheWindow : testing::Test
{
    Window *wnd{Window::getInstance(&engine)};
};

TEST_F(TheWindow, CanClearItsContents)
{
    wnd->clear(glm::u8vec4(0, 0, 0, 255));
}

TEST_F(TheWindow, CanPresentARenderer)
{
    DummyRenderer renderer;
    wnd->present(&renderer);
}
