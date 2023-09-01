#include "../include/InteractionManager.h"

#include <algorithm>
#include <stdexcept>

bool InteractionManager::hasIInteraction(IInteraction *interaction) const
{
    return std::find(std::begin(m_interactions), std::end(m_interactions), interaction) != std::end(m_interactions);
}

void InteractionManager::addIInteraction(IInteraction *interaction, IInteractionListener *)
{
    if (!interaction)
    {
        throw std::runtime_error{"Attempt to add a null interaction!"};
    }
    m_interactions.push_back(interaction);
}

void InteractionManager::handleInteractions() const
{
    for (auto interaction : m_interactions)
    {
        interaction->checkInteraction();
    }
}
