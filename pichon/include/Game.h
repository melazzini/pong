#pragma once

class Game
{
  public:
    void setRunning(bool trueFalse)
    {
        m_running = trueFalse;
    }

    [[nodiscard]] bool isRunning() const
    {
        return m_running;
    }

  private:
    bool m_running;
};
