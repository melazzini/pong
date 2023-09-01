#include "InteractionManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Mock;
using testing::Ne;

TEST(AnIInteractionManager, CanAddIInteractions)
{
    InteractionManager interactionManager;
    IInteraction dummyIInteraction{};
    IInteractionListener listener{};
    ASSERT_FALSE(interactionManager.hasIInteraction(&dummyIInteraction));
    interactionManager.addIInteraction(&dummyIInteraction, &listener);
    ASSERT_TRUE(interactionManager.hasIInteraction(&dummyIInteraction));
}

TEST(AnIInteractionManager, ThrowsIfYouPassItANullInteraction)
{
    InteractionManager interactionManager;
    IInteractionListener listener{};
    ASSERT_THROW(interactionManager.addIInteraction(nullptr, &listener), std::runtime_error);
}
