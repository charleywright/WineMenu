#include <windows.h>
#include "common.hpp"
#include <thread>
#include "logger.hpp"
#include <memory>
#include "game.hpp"
#include <chrono>
#include "hooking.hpp"
#include "config.hpp"
#include "invoker.hpp"
#include "natives.hpp"
#include "ui/d3dRenderer.hpp"
#include "ui/uiRenderer.hpp"

BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
  using namespace std::chrono_literals;
  using namespace Wine;

  if (reason == DLL_PROCESS_ATTACH)
  {
    g_Module = hInstance;
    CreateThread(
        nullptr, 0, [](LPVOID) -> DWORD
        {
          g_ModuleDir = GetModulePath(g_Module);
          g_DataDir = GetDataDir();

          g_Logger = std::make_unique<Logger>();
          g_Logger->Info("WineMenu injected.");

          g_Config = std::make_unique<Config>();
          g_Config->Load();

          g_Logger->RenderConsole(g_Config->m_RenderConsole);
          g_Logger->ShowConsole(g_Config->m_ShowConsole);

          g_GameVariables = std::make_unique<GameVariables>();
          g_GameFunctions = std::make_unique<GameFunctions>();

          bool wasGtaLoaded = true;
          while (*g_GameVariables->m_GameState != 0)
          {
            wasGtaLoaded = false;
            std::this_thread::sleep_for(2s);
            std::this_thread::yield();
          }
          if (!wasGtaLoaded)
            g_Logger->Info("Loaded GTA");

          g_D3DRenderer = std::make_unique<D3DRenderer>();
          g_UIRenderer = std::make_unique<UIRenderer>();

          g_Hooking = std::make_unique<Hooking>();
          g_Hooking->Hook();

          g_Invoker = std::make_unique<Invoker>();

          g_Logger->Info("Loaded WineMenu");
          g_UIRenderer->m_Opened ^= true;
          while (g_Running)
          {
            if (IsKeyPressed(VK_DELETE))
              g_Running = false;

            std::this_thread::sleep_for(3ms);
            std::this_thread::yield();
          }

          g_Hooking->Unhook();

          g_D3DRenderer.reset();
          g_Invoker.reset();
          g_Hooking.reset();
          g_GameVariables.reset();
          g_GameFunctions.reset();

          g_Config->Save();
          g_Config.reset();

          g_Logger->Info("WineMenu unloaded");
          g_Logger.reset();
          FreeLibraryAndExitThread(g_Module, 0);
        },
        nullptr, 0, nullptr);
  }

  return true;
}
