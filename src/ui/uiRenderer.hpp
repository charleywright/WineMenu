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

    void HandleInput();
    void RenderGTA();
    void RenderD3D();

    bool m_Opened = false;
    bool m_Sounds = true;
    bool m_MouseLocked = true;

  private:
    uint32_t m_OpenDelay = 30;
  };

  inline std::unique_ptr<UIRenderer> g_UIRenderer;
}