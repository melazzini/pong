#include "InteractionManager.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <stdexcept>

using testing::Eq;
using testing::Mock;
using testing::Ne;
using testing::Return;

struct DummyInteractionListener : IInteractionListener
{
    MOCK_METHOD(void, onInteraction, (const InteractionInfo &), (override));
};

struct DummyInteraction : IInteraction
{
    MOCK_METHOD(std::optional<InteractionInfo>, checkInteraction, (), (const override));
};

struct AnInteractionManager : testing::Test
{
    InteractionManager interactionManager{};
    DummyInteraction dummyInteraction{};
    DummyInteractionListener dummylistener{};
};

TEST_F(AnInteractionManager, CanAddIInteractions)
{
    ASSERT_FALSE(interactionManager.hasIInteraction(&dummyInteraction));
    interactionManager.addIInteraction(&dummyInteraction, &dummylistener);
    ASSERT_TRUE(interactionManager.hasIInteraction(&dummyInteraction));
}

TEST_F(AnInteractionManager, ThrowsIfYouPassItANullInteraction)
{
    ASSERT_THROW(interactionManager.addIInteraction(nullptr, &dummylistener), std::runtime_error);
}

TEST_F(AnInteractionManager, UsesTheInteractionObjectItselfToCheckForInteractions)
{
    interactionManager.addIInteraction(&dummyInteraction, &dummylistener);
    EXPECT_CALL(dummyInteraction, checkInteraction);
    interactionManager.handleInteractions();
}

TEST_F(AnInteractionManager,
       NotifiesTheCorrespondingListenerAboutAnInteractionWithAnInteractionInfoObtainedFromInteractionObject)
{
    InteractionInfo dummyInteractionInfo{};
    interactionManager.addIInteraction(&dummyInteraction, &dummylistener);
    EXPECT_CALL(dummyInteraction, checkInteraction).WillOnce(Return(dummyInteractionInfo));
    EXPECT_CALL(dummylistener, onInteraction(dummyInteractionInfo));
    interactionManager.handleInteractions();
}
