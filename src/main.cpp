#include <windows.h>
#include "common.hpp"
#include <thread>
#include "logger.hpp"
#include <memory>
#include "game.hpp"
#include "util.hpp"
#include <chrono>

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
          g_Logger->Info("Loaded game variables");

          int counter = 0;
          while(g_Running)
          {
            if(IsKeyPressed(VK_DELETE))
              g_Running = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            std::this_thread::yield();
          }

          g_Logger->Info("WineMenu unloaded");
          g_Logger.reset();
          FreeLibraryAndExitThread(g_Module, 0);
        },
        nullptr, 0, nullptr);
  }

  return true;
}
