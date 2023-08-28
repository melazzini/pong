#pragma once
#include "Interfaces.h"

class Event : public IEvent
{
  public:
    Event(EventType type) : m_type{type}
    {
    }

    EventType eventType() const override
    {
        return m_type;
    }

    ~Event() = default;

  private:
    EventType m_type;
};
