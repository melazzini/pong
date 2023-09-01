#pragma once
#include <tuple>
#include <utility>
#include <vector>

struct IInteraction
{
    [[nodiscard]] virtual bool checkInteraction() const = 0;
};

class InteractionInfo
{
};

struct IInteractionListener
{
    virtual void onInteraction(const InteractionInfo &info) = 0;
};

class InteractionManager
{
  public:
    void addIInteraction(IInteraction *interaction, IInteractionListener *);
    bool hasIInteraction(IInteraction *interaction) const;
    void handleInteractions() const;

  private:
    std::vector<std::pair<IInteractionListener *, IInteraction *>> m_interactions;
};
