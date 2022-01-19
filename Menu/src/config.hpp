#pragma once
#include <memory>

namespace Wine
{
  class Config
  {
  public:
    Config() = default;
    ~Config() noexcept = default;
    Config(Config const &) = delete;
    Config(Config &&) = delete;
    Config &operator=(Config const &) = delete;
    Config &operator=(Config &&) = delete;

    /**
     * @brief Load the last saved state
     * 
     */
    void Load();

    /**
     * @brief Save the current state
     */
    void Save();

    bool m_Sounds = true;
    bool m_MouseLocked = true;
    bool m_RenderConsole = true;
    bool m_ShowConsole = false;

  private:
  };

  inline std::unique_ptr<Config> g_Config;
}