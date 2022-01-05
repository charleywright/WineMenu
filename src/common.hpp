#include <windows.h>
#include <fstream>

#pragma once

namespace Wine {
  inline HMODULE g_Module{};
  inline bool g_Running = true;
  inline std::string g_ModulePath;
}
