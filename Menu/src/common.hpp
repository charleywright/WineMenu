#pragma once
#include "game.hpp"
#include <windows.h>
#include <fstream>
#include <windows.h>
#include <shlwapi.h>
#include <filesystem>

namespace Wine
{
  /**
   * @brief Get the path to the appdata dir
   * 
   * @return The absolute path to data dir
   */
  inline std::filesystem::path GetDataDir()
  {
    char *appdata;
    size_t appdata_len;
    _dupenv_s(&appdata, &appdata_len, "APPDATA");
    std::filesystem::path dir = appdata;
    dir /= "WineMenu";
    if (std::filesystem::exists(dir) && !std::filesystem::is_directory(dir))
      std::filesystem::remove(dir);
    if (!std::filesystem::exists(dir))
      std::filesystem::create_directory(dir);
  }

  /**
   * @brief Get the path to a loaded module
   * 
   * @param module The module to get the path of
   * @return The absolute path to the module
   */
  inline std::filesystem::path GetModulePath(HMODULE module)
  {
    std::filesystem::path path;
    char buffer[MAX_PATH];
    GetModuleFileNameA(module, buffer, MAX_PATH);
    PathRemoveFileSpecA(buffer);
    path = buffer;
    return path;
  }

  /**
	 * \brief Checks if a key is pressed
	 * \param key A virtual key code
	 * \return bool
	 */
  inline bool IsKeyPressed(std::uint16_t key)
  {
    if (GetForegroundWindow() == g_GameVariables->m_GameWindow)
    {
      if (GetAsyncKeyState(key) & 0x8000)
      {
        return true;
      }
    }

    return false;
  }

  inline HMODULE g_Module{};
  inline bool g_Running = true;
  inline std::filesystem::path g_ModuleDir;
  inline std::filesystem::path g_DataDir;
}
