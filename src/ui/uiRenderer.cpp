#include "uiRenderer.hpp"
#include "util.hpp"
#include "game.hpp"
#include "natives.hpp"
#include "logger.hpp"
#include "timer.hpp"
#include <chrono>
#include <winuser.h>

#include "gta.hpp"

using namespace std::chrono_literals;

namespace Wine
{
  namespace
  {
    Timer openTimer = Timer(100ms);
    Timer logTimer = Timer(100ms);
    Timer featureTimer = Timer(100ms);
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

    if (IsKeyPressed(VK_F4) && featureTimer.Update())
    {
      g_Logger->Info("Feature key pressed");
    }
  };

  void UIRenderer::RenderGTA()
  {
    if (m_Opened && m_MouseLocked)
    {
      // There are others, also this doesn't account for remapped controls, but it's for debugging so ¯\_(ツ)_/¯
      PAD::DISABLE_CONTROL_ACTION(0, 1, true);
      PAD::DISABLE_CONTROL_ACTION(0, 2, true);
      PAD::DISABLE_CONTROL_ACTION(0, 4, true);
      PAD::DISABLE_CONTROL_ACTION(0, 6, true);
    }
  }

  void UIRenderer::RenderD3D()
  {
    if (m_Opened)
      g_Logger->Render();
  }
}