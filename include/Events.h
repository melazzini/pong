#pragma once

#include "EventManagementInterface.h"
#include "utils.h"

class EventQuit : public IEvent
{
  public:
    EventType eventType() const override
    {
        return EventType::QUIT;
    }
};
class ArrowKeyPressed : public IEvent
{
  public:
    ArrowKeyPressed(ArrowKey key) : m_key(key)
    {
    }
    EventType eventType() const override
    {
        return EventType::ARROW_KEYS_PRESSED;
    }

    ArrowKey key() const
    {
        return m_key;
    }

  private:
    ArrowKey m_key;
};
