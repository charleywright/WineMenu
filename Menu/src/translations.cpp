#include "translations.hpp"
#include "common.hpp"
#include "json.hpp"
#include <fstream>
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
    std::vector<std::pair<std::string, std::string>>::iterator it = std::find_if(m_Translations.begin(), m_Translations.end(),
                                                                                 [&key](const std::pair<std::string, std::string> &element)
                                                                                 { return element.first == key; });
    return (*it).second;
  }
}