#include "Window.h"
#include "gmock/gmock.h"
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
    MOCK_METHOD(void, clearWindow, (glm::u8vec4), (override));

    MOCK_METHOD(void, updateWindow, (), (override));
};

struct DummyBackendContext : IBackendContext
{
    DummyWindowPrimitive *windowPrimitiveSpy{};
    std::unique_ptr<IRendererPrimitive> rendererPrimitive() override
    {
        return std::make_unique<DummyRendererPrimitive>();
    }

    std::unique_ptr<IWindowPrimitive> windowPrimitive() override
    {
        auto ptr = std::make_unique<DummyWindowPrimitive>();
        windowPrimitiveSpy = ptr.get();
        return ptr;
    }
};

struct TheWindow : testing::Test
{
    inline static Window *wnd;
    DummyBackendContext engine;
    inline static DummyWindowPrimitive *windowPrimitiveSpy{};
    inline static const glm::u8vec4 dummyBackgroundColor{glm::u8vec4(0, 0, 0, 255)};

    void SetUp()
    {
        if (windowPrimitiveSpy == nullptr)
        {
            wnd = Window::getInstance(&engine);
            windowPrimitiveSpy = engine.windowPrimitiveSpy;
        }
    }
};

TEST_F(TheWindow, ClearsItsContentsUsingThePrimitive)
{
    EXPECT_CALL(*windowPrimitiveSpy, clearWindow);
    wnd->clear(dummyBackgroundColor);
    testing::Mock::VerifyAndClearExpectations(windowPrimitiveSpy);
}

TEST_F(TheWindow, IsASingleton)
{
    Window *wnd1 = Window::getInstance(&engine);
    Window *wnd2 = Window::getInstance(&engine);
    ASSERT_THAT(wnd1, Eq(wnd2));
}

TEST_F(TheWindow, ShowsItselfUsingItsPrimitive)
{
    EXPECT_CALL(*windowPrimitiveSpy, updateWindow);
    wnd->present();
    testing::Mock::VerifyAndClearExpectations(windowPrimitiveSpy);
}
