#include "config.hpp"
#include "common.hpp"
#include <fstream>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;

namespace Wine
{
  void Config::Load()
  {
    std::filesystem::path path = g_DataDir;
    path.append("config.json");
    std::fstream file;
    file.open(path);
    json data = json::parse(file);
    m_Sounds = data.value("Sounds", m_Sounds);
    m_MouseLocked = data.value("MouseLocked", m_MouseLocked);
    m_RenderConsole = data.value("RenderConsole", m_RenderConsole);
    m_ShowConsole = data.value("ShowConsole", m_ShowConsole);
    file.close();
  }

  void Config::Save()
  {
    json j;
    j["Sounds"] = m_Sounds;
    j["MouseLocked"] = m_MouseLocked;
    j["RenderConsole"] = m_RenderConsole;
    j["ShowConsole"] = m_ShowConsole;

    std::filesystem::path path = g_DataDir;
    path.append("config.json");
    std::ofstream file;
    file.open(path);
    file << j << std::endl;
    file.close();
  }
}