#pragma once
#include <cstdint>
#include <memory>

namespace Wine
{
  class UIRenderer
  {
  public:
    UIRenderer() = default;
    ~UIRenderer() noexcept = default;
    UIRenderer(UIRenderer const &) = delete;
    UIRenderer(UIRenderer &&) = delete;
    UIRenderer &operator=(UIRenderer const &) = delete;
    UIRenderer &operator=(UIRenderer &&) = delete;

    /**
     * @brief Handles input event for hotkeys
     */
    void HandleInput();

    /**
     * @brief Renders any native UI
     */
    void RenderGTA();

    /**
     * @brief Renders any DirectX UI
     * 
     */
    void RenderD3D();

    bool m_Opened = false;

  private:
    uint32_t m_OpenDelay = 30;
  };

  inline std::unique_ptr<UIRenderer> g_UIRenderer;
}