#include "uiRenderer.hpp"
#include "util.hpp"
#include "game.hpp"
#include "natives.hpp"
#include "logger.hpp"
#include "timer.hpp"
#include <chrono>
#include <winuser.h>

using namespace std::chrono_literals;

namespace Wine
{
  namespace
  {
    Timer openTimer = Timer(100ms);
    Timer logTimer = Timer(100ms);
  }

  void UIRenderer::HandleInput()
  {
    if (IsKeyPressed(VK_INSERT) && openTimer.Update())
    {
      m_Opened ^= true;
      if (m_Sounds)
        AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
    }

    if (IsKeyPressed(VK_END) && logTimer.Update())
      g_Logger->ShowConsole(!g_Logger->ShowConsole());
  };

  void UIRenderer::RenderGTA()
  {
    if (m_Opened && m_MouseLocked)
      PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
  }

  void UIRenderer::RenderD3D()
  {
    if (m_Opened)
      g_Logger->Render();
  }
}