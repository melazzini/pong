#pragma once
#include <vector>

class IInteraction
{
};

class IInteractionListener
{
};

class InteractionManager
{
  public:
    void addIInteraction(IInteraction *interaction, IInteractionListener *);
    bool hasIInteraction(IInteraction *interaction) const;

  private:
    std::vector<IInteraction *> m_interactions;
};
