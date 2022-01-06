#include <windows.h>
#include "common.hpp"
#include <thread>
#include "logger.hpp"
#include <memory>
#include "game.hpp"
#include "util.hpp"
#include <chrono>
#include "hooking.hpp"

BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
  using namespace Wine;

  if (reason == DLL_PROCESS_ATTACH)
  {
    g_Module = hInstance;
    CreateThread(
        nullptr, 0, [](LPVOID) -> DWORD
        {
          g_Logger = std::make_unique<Logger>();
          g_Logger->Info("WineMenu injected.");

          g_GameVariables = std::make_unique<GameVariables>();
          g_GameFunctions = std::make_unique<GameFunctions>();
          std::string title = "WineMenu - GTA ";
          title.append(g_GameVariables->m_GameBuild);
          g_Logger->SetTitle(title.c_str());

          bool wasGtaLoaded = true;
          while (*g_GameVariables->m_GameState != 0)
          {
            wasGtaLoaded = false;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::this_thread::yield();
          }
          if(!wasGtaLoaded) g_Logger->Info("Loaded GTA");

          g_Hooking = std::make_unique<Hooking>();
          g_Hooking->Hook();

          g_Logger->Info("Loaded WineMenu");
          while (g_Running)
          {
            if (IsKeyPressed(VK_DELETE))
              g_Running = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            std::this_thread::yield();
          }
          // std::this_thread::sleep_for(std::chrono::milliseconds(500));

          g_Hooking->Unhook();

          // std::this_thread::sleep_for(std::chrono::milliseconds(500));

          g_Hooking.reset();
          g_GameVariables.reset();
          g_GameFunctions.reset();

          g_Logger->Info("WineMenu unloaded");
          g_Logger.reset();
          FreeLibraryAndExitThread(g_Module, 0);
        },
        nullptr, 0, nullptr);
  }

  return true;
}
