#pragma once
#include <memory>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>
class IInteractionInfo
{
};

struct IInteraction
{
    [[nodiscard]] virtual std::optional<std::unique_ptr<IInteractionInfo>> checkInteraction() const = 0;
};

struct IInteractionListener
{
    virtual void onInteraction(std::unique_ptr<IInteractionInfo> info) = 0;
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
