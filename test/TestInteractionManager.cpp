#include "InteractionManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Mock;
using testing::Ne;

struct AnInteractionManager : testing::Test
{
    InteractionManager interactionManager{};
    IInteraction dummyIInteraction{};
    IInteractionListener dummylistener{};
};

TEST_F(AnInteractionManager, CanAddIInteractions)
{
    ASSERT_FALSE(interactionManager.hasIInteraction(&dummyIInteraction));
    interactionManager.addIInteraction(&dummyIInteraction, &dummylistener);
    ASSERT_TRUE(interactionManager.hasIInteraction(&dummyIInteraction));
}

TEST_F(AnInteractionManager, ThrowsIfYouPassItANullInteraction)
{
    ASSERT_THROW(interactionManager.addIInteraction(nullptr, &dummylistener), std::runtime_error);
}
