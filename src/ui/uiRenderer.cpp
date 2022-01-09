#include "uiRenderer.hpp"
#include "util.hpp"
#include "game.hpp"
#include "natives.hpp"
#include "logger.hpp"
#include <winuser.h>

namespace Wine
{
  namespace
  {
    uint32_t openTicker = 0;
    uint32_t logTicker = 0;
  }

  void UIRenderer::HandleInput()
  {
    bool openKeyPressed = IsKeyPressed(VK_INSERT);
    if (openKeyPressed && *g_GameVariables->m_FrameCount - openTicker >= m_OpenDelay)
    {
      openTicker = *g_GameVariables->m_FrameCount;
      m_Opened ^= true;

      if (m_Sounds)
        AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
    }

    bool logKeyPressed = IsKeyPressed(VK_END);
    if (logKeyPressed && *g_GameVariables->m_FrameCount - logTicker >= m_OpenDelay)
    {
      logTicker = *g_GameVariables->m_FrameCount;
      g_Logger->ShowConsole(!g_Logger->ShowConsole());
    }
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