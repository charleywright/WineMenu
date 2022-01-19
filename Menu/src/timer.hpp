#pragma once

namespace Wine
{
  class Timer
  {
  public:
    explicit Timer(std::chrono::milliseconds delay) : m_Timer(std::chrono::high_resolution_clock::now()),
                                                      m_Delay(std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(delay))
    {
    }

    /**
     * @brief Checks if the delay has passed
     * 
     * @return true 
     * @return false 
     */
    bool Update()
    {
      auto now = std::chrono::high_resolution_clock::now();
      if ((now.time_since_epoch() - m_Timer.time_since_epoch()).count() >= m_Delay.count())
      {
        m_Timer = now;
        return true;
      }

      return false;
    }

    /**
     * @brief Set the timer's delay
     * 
     * @param delay The delay to set
     */
    void SetDelay(std::chrono::milliseconds delay)
    {
      m_Delay = delay;
    }

  private:
    std::chrono::high_resolution_clock::time_point m_Timer;
    std::chrono::high_resolution_clock::duration m_Delay;
  };
}