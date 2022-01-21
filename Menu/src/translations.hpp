#pragma once
#include <vector>
#include <utility>
#include <memory>
#include <string>

namespace Wine
{
  class Translations
  {
  public:
    Translations() = default;
    ~Translations() noexcept = default;
    Translations(Translations const &) = delete;
    Translations(Translations &&) = delete;
    Translations &operator=(Translations const &) = delete;
    Translations &operator=(Translations &&) = delete;

    /**
     * @brief Load translations.json
     * @return If translations were loaded successfully
     */
    bool Load();

    /**
     * @brief Get a translation by name
     */
    std::string Get(std::string name);

  private:
    std::vector<std::pair<std::string, std::string>> m_Translations;
  };

  inline std::unique_ptr<Translations> g_Translations;
}