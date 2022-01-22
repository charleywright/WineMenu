#include "translations.hpp"
#include "common.hpp"
#include "json.hpp"
#include <fstream>
#include <algorithm>
#include "logger.hpp"

namespace Wine
{
  bool Translations::Load()
  {
    std::filesystem::path file(g_DataDir);
    file.append("translations.json");
    if (!std::filesystem::exists(file))
      return false;
    nlohmann::json translations;
    std::fstream file_data;
    file_data.open(file);
    try
    {
      file_data >> translations;
      if (!translations.is_object())
        return false;

      for (auto &[key, value] : translations.items())
        m_Translations.push_back(std::pair<std::string, std::string>(key, value));
    }
    catch (nlohmann::json::exception &)
    {
      return false;
    }
    file_data.close();
    return true;
  }

  std::string Translations::Get(std::string key)
  {
    if (m_Translations.size() == 0)
      return "NO_TRANSLATION";
    auto it = std::find_if(m_Translations.begin(), m_Translations.end(),
                           [&key](const std::pair<std::string, std::string> &element)
                           { return element.first == key; });
    if ((*it).first != key)
      return "NO_TRANSLATION";
    if ((*it).second.length() == 0)
      return (*it).first;
    return (*it).second;
  }
}