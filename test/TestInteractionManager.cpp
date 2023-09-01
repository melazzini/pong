#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

using testing::Eq;
using testing::Mock;
using testing::Ne;

class IInteraction
{
};

class IInteractionListener
{
};

class InteractionManager
{
  public:
    void addIInteraction(IInteraction *interaction, IInteractionListener *)
    {
        if (!interaction)
        {
            throw std::runtime_error{"Attempt to add a null interaction!"};
        }
        m_interactions.push_back(interaction);
    }
    bool hasIInteraction(IInteraction *interaction)
    {
        return std::find(std::begin(m_interactions), std::end(m_interactions), interaction) != std::end(m_interactions);
    }

  private:
    std::vector<IInteraction *> m_interactions;
};

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
