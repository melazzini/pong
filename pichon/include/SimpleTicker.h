#pragma once
#include "Interfaces.h"
#include <chrono>
#include <thread>

class SimpleTicker : public ITicker
{
  public:
    SimpleTicker(std::chrono::milliseconds period) : m_period{period}, m_previousTime{std::chrono::system_clock::now()}
    {
    }

    std::chrono::milliseconds tick() override
    {
        auto currentTime{std::chrono::system_clock::now()};
        auto dTime{currentTime - m_previousTime};
        if (dTime < m_period)
        {
            std::this_thread::sleep_for(m_period - dTime);
            currentTime = std::chrono::system_clock::now();
            dTime = currentTime - m_previousTime;
        }
        m_previousTime = currentTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(dTime);
    }

  private:
    std::chrono::milliseconds m_period;
    std::chrono::time_point<std::chrono::system_clock> m_previousTime;
};

