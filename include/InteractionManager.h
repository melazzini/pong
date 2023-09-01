#pragma once
#include <vector>

struct IInteraction
{
    [[nodiscard]] virtual bool checkInteraction() const = 0;
};

class IInteractionListener
{
};

class InteractionManager
{
  public:
    void addIInteraction(IInteraction *interaction, IInteractionListener *);
    bool hasIInteraction(IInteraction *interaction) const;
    void handleInteractions() const;

  private:
    std::vector<IInteraction *> m_interactions;
};
