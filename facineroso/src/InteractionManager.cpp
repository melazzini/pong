#include "../include/InteractionManager.h"
#include <memory>
#include <optional>

#include <algorithm>
#include <stdexcept>

bool InteractionManager::hasIInteraction(IInteraction *interaction) const
{
    return std::find_if(std::begin(m_interactions), std::end(m_interactions),
                        [interaction](const auto &listenerInteractionPair) {
                            return listenerInteractionPair.second == interaction;
                        }) != std::end(m_interactions);
}

void InteractionManager::addIInteraction(IInteraction *interaction, IInteractionListener *interactionListener)
{
    if (!interaction)
    {
        throw std::runtime_error{"Attempt to add a null interaction!"};
    }
    m_interactions.push_back({interactionListener, interaction});
}

void InteractionManager::handleInteractions() const
{
    for (auto listenerInteractionPair : m_interactions)
    {
        if (std::optional<std::unique_ptr<IInteractionInfo>> info{listenerInteractionPair.second->checkInteraction()};
            info.has_value())
        {
            listenerInteractionPair.first->onInteraction(std::move(info.value()));
        }
    }
}
