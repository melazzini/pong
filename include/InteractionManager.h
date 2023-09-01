#pragma once
#include <optional>
#include <tuple>
#include <utility>
#include <vector>
class InteractionInfo
{
};

inline bool operator==(const InteractionInfo &a, const InteractionInfo &b)
{
    return true;
}

struct IInteraction
{
    [[nodiscard]] virtual std::optional<InteractionInfo> checkInteraction() const = 0;
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
